#include <GL/glew.h>
#include "program/maze_renderer.hpp"
#include "program/maze.hpp"

MazeRenderer::MazeRenderer(Maze& maze, GLfloat cellSize) : maze(maze), cellSize(cellSize) {
    // Add later if needed
}

MazeRenderer::~MazeRenderer() {
    // Add later if needed
}

void MazeRenderer::drawMaze() {
    const auto& grid = maze.getGrid();

    glBegin(GL_QUADS);
    for (int i = 0; i < maze.getGridRows(); i++) {
        for (int j = 0; j < maze.getGridCols(); j++) {
            if (grid[i][j].wall) {
                glColor3f(0.3f, 0.3f, 0.3f); // darker grey
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // white
            }

            drawCell(j, i);
        }
    }
    glEnd();
}

void MazeRenderer::drawAIPath(const vector<pair<int, int>>& path) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    for (auto [x, y] : path) {
        drawCell(x, y);
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