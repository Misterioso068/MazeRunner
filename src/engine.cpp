#include <GL/glew.h>
#include <stdexcept>
#include <memory>
#include "program/engine.hpp"

Engine::Engine(int width, int height, int rows, int cols, int cellSize, double loopChance)
    : window("Maze Runner", width, height),
      maze(rows, cols, loopChance),
      mazeRenderer(maze, cellSize),
      running(true),
      drawPath(false),
      redrawMaze(false)
{
    if (!window.init()) {
        throw runtime_error("Failed to initialize window");
    }

    mazeRenderer.updateProjection();
}

void Engine::run() {
    unique_ptr<MazeAI> bfsAI = make_unique<BFS_AI>();
    unique_ptr<MazeAI> dfsAI = make_unique<DFS_AI>();
    unique_ptr<MazeAI> astarAI = make_unique<A_STAR_AI>();

    int bfsStartX = 1, bfsStartY = 1;
    int dfsStartX = 999, dfsStartY = 1;
    int astarStartX = 1, astarStartY = 999;
    int goalX = 499, goalY = 499;

    bfsAI->findPath(maze, bfsStartX, bfsStartY, goalX, goalY);
    dfsAI->findPath(maze, dfsStartX, dfsStartY, goalX, goalY);
    astarAI->findPath(maze, astarStartX, astarStartY, goalX, goalY);

    Color wall = {0.3f, 0.3f, 0.3f};
    Color path = {1.0f, 1.0f, 1.0f};
    Color dfsPathColor = {0.0f, 0.0f, 1.0f};
    Color bfsPathColor = {1.0f, 0.0f, 0.0f};
    Color astarPathColor = {0.0f, 1.0f, 0.0f};

    Uint32 stepDelay = 1;
    PathAnimator bfsAnimator(bfsAI->getPath().size(), stepDelay);
    PathAnimator dfsAnimator(dfsAI->getPath().size(), stepDelay);
    PathAnimator astarAnimator(astarAI->getPath().size(), stepDelay);

    while (running) {
        running = window.handleEvents(drawPath, redrawMaze);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        mazeRenderer.drawMaze(wall, path);

        const auto& bfsAIPath = bfsAI->getPath();
        const auto& dfsAIPath = dfsAI->getPath();
        const auto& astarAIPath = astarAI->getPath();

        if (!drawPath) {
            // Animate the full path slowly
            bfsAnimator.update();
            dfsAnimator.update();
            astarAnimator.update();

            mazeRenderer.drawAIPathAnimated(bfsAIPath, bfsAnimator.getIndex(), bfsPathColor);
            mazeRenderer.drawAIPathAnimated(dfsAIPath, dfsAnimator.getIndex(), dfsPathColor);
            mazeRenderer.drawAIPathAnimated(astarAIPath, astarAnimator.getIndex(), astarPathColor);
        }

        if (drawPath) {
            // Static draw full path
            mazeRenderer.drawAIPath(bfsAIPath, bfsPathColor);
            mazeRenderer.drawAIPath(dfsAIPath, dfsPathColor);
            mazeRenderer.drawAIPath(astarAIPath, astarPathColor);
        }

        if (redrawMaze) {
            maze.generate();
            bfsAI->findPath(maze, bfsStartX, bfsStartY, goalX, goalY);
            dfsAI->findPath(maze, dfsStartX, dfsStartY, goalX, goalY);
            astarAI->findPath(maze, astarStartX, astarStartY, goalX, goalY);

            bfsAnimator.reset(bfsAI->getPath().size());
            dfsAnimator.reset(dfsAI->getPath().size());
            astarAnimator.reset(astarAI->getPath().size());

            redrawMaze = false;
        }

        window.swap();
    }
}
