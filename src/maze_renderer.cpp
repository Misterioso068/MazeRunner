#include <GL/glew.h>
#include "program/maze_renderer.hpp"
#include "program/maze.hpp"

// Helper to convert Color to unsigned char (RGB). Needed for texture creation
struct RGB {
    unsigned char r, g, b;
};

MazeRenderer::MazeRenderer(Maze& maze, GLfloat cellSize) : maze(maze), cellSize(cellSize), mazeTexture(0){
    // Add later if needed
}

MazeRenderer::~MazeRenderer() {
    if (mazeTexture != 0) {
        glDeleteTextures(1, &mazeTexture);
        mazeTexture = 0;
    }
}

MazeRenderer::MazeRenderer(MazeRenderer&& other) noexcept
    : maze(other.maze), cellSize(other.cellSize), mazeTexture(other.mazeTexture) 
{
    other.mazeTexture = 0;
}

MazeRenderer& MazeRenderer::operator=(MazeRenderer&& other) noexcept {
    if (this != &other) {
        // Clean up current texture
        if (mazeTexture != 0) {
            glDeleteTextures(1, &mazeTexture);
        }

        // Steal resources
        mazeTexture = other.mazeTexture;
        cellSize    = other.cellSize;
        // maze is a reference, so we can't rebind it — we assume both use the same Maze.

        // Leave 'other' safe
        other.mazeTexture = 0;
    }
    return *this;
}


void MazeRenderer::createMazeTexture(const Color& wall, const Color& path, const Color& water, bool drawWater) {
    const auto& grid = maze.getGrid();
    int r = maze.getGridRows();
    int c = maze.getGridCols();

    vector<RGB> pixels(r * c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            RGB color;
            if (grid[i][j].wall) {
                color = {
                    (unsigned char)(wall.r * 255.0f),
                    (unsigned char)(wall.g * 255.0f),
                    (unsigned char)(wall.b * 255.0f)
                };
            }
            else if (grid[i][j].water && drawWater) {
                color = {
                    (unsigned char)(water.r * 255.0f),
                    (unsigned char)(water.g * 255.0f),
                    (unsigned char)(water.b * 255.0f)
                };
            }
            else {
                color = {
                    (unsigned char)(path.r * 255.0f),
                    (unsigned char)(path.g * 255.0f),
                    (unsigned char)(path.b * 255.0f)
                };
            }

            pixels[i * c + j] = color;
        }
    }

    if (mazeTexture != 0) {
        glDeleteTextures(1, &mazeTexture);
        mazeTexture = 0;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &mazeTexture);
    glBindTexture(GL_TEXTURE_2D, mazeTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, c, r, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void MazeRenderer::drawMaze() {
    if (mazeTexture == 0) return;
    glColor3f(1.0f, 1.0f, 1.0f);

    int r = maze.getGridRows();
    int c = maze.getGridCols();

    GLfloat width = c * cellSize;
    GLfloat height = r * cellSize;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mazeTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0, height);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void MazeRenderer::drawAIPath(const vector<pair<int, int>>& path, const Color& c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_QUADS);
    for (auto [x, y] : path) {
        drawCell(x, y);
    }
    glEnd();
}

void MazeRenderer::drawAIPathAnimated(const vector<pair<int, int>>& path, size_t index, const Color& c) {
    glColor3f(c.r, c.g, c.b);
    glBegin(GL_QUADS);
    for (size_t i = 0; i < index; i++) {
        drawCell(path[i].first, path[i].second);
    }
    glEnd();
}

void MazeRenderer::drawCell(int x, int y) {
    GLfloat scaledX = x * cellSize;
    GLfloat scaledY = y * cellSize;

    glVertex2f(scaledX, scaledY);
    glVertex2f(scaledX + cellSize, scaledY);
    glVertex2f(scaledX + cellSize, scaledY + cellSize);
    glVertex2f(scaledX, scaledY + cellSize);
}

void MazeRenderer::updateCellSize(GLfloat newCellSize) {
    cellSize = newCellSize;
}