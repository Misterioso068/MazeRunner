#include <GL/glew.h>
#include "program/maze_renderer.hpp"
#include "program/maze.hpp"

MazeRenderer::MazeRenderer(Maze& maze, GLfloat cellSize) : maze(maze), cellSize(cellSize) {
    // Add later if needed
}

MazeRenderer::~MazeRenderer() {
    // Add later if needed
}

void MazeRenderer::drawMaze(const Color& wall, const Color& path) {
    const auto& grid = maze.getGrid();

    glBegin(GL_QUADS);
    for (int i = 0; i < maze.getGridRows(); i++) {
        for (int j = 0; j < maze.getGridCols(); j++) {
            if (grid[i][j].wall) {
                glColor3f(wall.r, wall.g, wall.b); // darker grey
            } else {
                glColor3f(path.r, path.g, path.b); // white
            }

            drawCell(j, i);
        }
    }
    glEnd();
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

void MazeRenderer::updateProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, maze.getGridCols() * cellSize, maze.getGridRows() * cellSize, 0, -1, 1); // origin at top-left
    glMatrixMode(GL_MODELVIEW);
}

void MazeRenderer::updateCellSize(GLfloat newCellSize) {
    cellSize = newCellSize;
    updateProjection();
}