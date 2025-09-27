#include <GL/glew.h>
#include <stdexcept>
#include <memory>
#include "program/engine.hpp"

Engine::Engine(int width, int height, int rows, int cols, int cellSize, double loopChance)
    : window("Maze Runner", width, height),
      maze(rows, cols, loopChance),
      mazeRenderer(maze, cellSize),
      running(true),
      drawPath(false)
{
    if (!window.init()) {
        throw runtime_error("Failed to initialize window");
    }

    mazeRenderer.updateProjection();
}

void Engine::run() {
    unique_ptr<MazeAI> bfsAI = make_unique<BFS_AI>();
    unique_ptr<MazeAI> dfsAI = make_unique<DFS_AI>();
    bfsAI->findPath(maze, 1, 1, maze.getGridRows() - 2, maze.getGridCols() - 2);
    dfsAI->findPath(maze, 1, 1, maze.getGridRows() - 2, maze.getGridCols() - 2);

    Color wall = {0.3f, 0.3f, 0.3f};
    Color path = {1.0f, 1.0f, 1.0f};
    Color dfsPathColor = {0.0f, 0.0f, 1.0f};
    Color bfsPathColor = {1.0f, 0.0f, 0.0f};

    while (running) {
        running = window.handleEvents(drawPath, redrawMaze);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        mazeRenderer.drawMaze(wall, path);

        if (drawPath) {
            mazeRenderer.drawAIPath(dfsAI->getPath(), dfsPathColor);
            mazeRenderer.drawAIPath(bfsAI->getPath(), bfsPathColor);
        }

        if (redrawMaze) {
            maze.generate();
            bfsAI->findPath(maze, 1, 1, maze.getGridRows() - 2, maze.getGridCols() - 2);
            dfsAI->findPath(maze, 1, 1, maze.getGridRows() - 2, maze.getGridCols() - 2);
            redrawMaze = false;
        }

        window.swap();
    }
}
