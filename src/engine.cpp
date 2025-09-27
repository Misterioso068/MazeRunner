#include <GL/glew.h>
#include <stdexcept>
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
    ai.BFSAIPathfinding(maze, 1, 1, rows*2-1, cols*2-1); // adjust end coordinates
}

void Engine::run() {
    while (running) {
        running = window.handleEvents(maze, ai, drawPath);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        mazeRenderer.drawMaze();

        if (drawPath) {
            mazeRenderer.drawAIPath(ai.getAIPath());
        }

        window.swap();
    }
}
