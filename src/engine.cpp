#include <GL/glew.h>
#include <stdexcept>
#include <memory>
#include <iostream>
#include "program/engine.hpp"

Engine::Engine(int width, int height, int rows, int cols, int cellSize, double loopChance, double waterChance)
    : window("Maze Runner", width, height),
      maze(rows, cols, loopChance, waterChance),
      mazeRenderer(maze, cellSize),
      running(true),
      drawPath(false),
      beginAnimation(false),
      drawWater(true),
      toggleWater(false),
      redrawMaze(false)
{
    if (!window.init()) {
        throw runtime_error("Failed to initialize window");
    }
}

void Engine::run() {
    unique_ptr<MazeAI> bfsAI = make_unique<BFS_AI>();
    unique_ptr<MazeAI> dfsAI = make_unique<DFS_AI>();
    unique_ptr<MazeAI> astarAI = make_unique<A_STAR_AI>();

    int bfsStartX = 1, bfsStartY = 1;
    int dfsStartX = 1, dfsStartY = 1;
    int astarStartX = 1, astarStartY = 1;
    int goalX = 3999, goalY = 3999;

    bfsAI->findPath(maze, bfsStartX, bfsStartY, goalX, goalY);
    dfsAI->findPath(maze, dfsStartX, dfsStartY, goalX, goalY);
    astarAI->findPath(maze, astarStartX, astarStartY, goalX, goalY);

    Color wall = {0.3f, 0.3f, 0.3f};
    Color path = {1.0f, 1.0f, 1.0f};
    Color water = {0.0f, 0.0f, 1.0f};

    Color dfsPathColor = {0.0f, 0.0f, 1.0f};
    Color bfsPathColor = {1.0f, 0.0f, 0.0f};
    Color astarPathColor = {0.0f, 1.0f, 0.0f};

    PathAnimator bfsAnimator(maze, bfsAI->getPath(), 1, 50);
    PathAnimator dfsAnimator(maze, dfsAI->getPath(), 1, 50);
    PathAnimator astarAnimator(maze, astarAI->getPath(), 1, 50);

    // Create Maze Texture for ompitmized performance
    mazeRenderer.createMazeTexture(wall, path, water, drawWater);

    // Movable Camera
    Camera2D cam;

    // FPS counter
    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;
    GLfloat fps = 0.0f;
    while (running) {
        running = window.handleEvents(drawPath, redrawMaze, beginAnimation, toggleWater, cam);

        if (toggleWater) {
            drawWater = !drawWater;
            mazeRenderer.createMazeTexture(wall, path, water, drawWater);
            toggleWater = false;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update camera projection
        cam.applyProjection(maze.getGridRows(), maze.getGridCols());

        glLoadIdentity();
        mazeRenderer.drawMaze();

        const auto& bfsAIPath = bfsAI->getPath();
        const auto& dfsAIPath = dfsAI->getPath();
        const auto& astarAIPath = astarAI->getPath();

        if (beginAnimation) {
            // Animate the full path slowly
            bfsAnimator.update();
            dfsAnimator.update();
            astarAnimator.update();

            mazeRenderer.drawAIPathAnimated(dfsAIPath, dfsAnimator.getIndex(), dfsPathColor);
            mazeRenderer.drawAIPathAnimated(astarAIPath, astarAnimator.getIndex(), astarPathColor);
            mazeRenderer.drawAIPathAnimated(bfsAIPath, bfsAnimator.getIndex(), bfsPathColor);
        }

        if (drawPath) {
            // Static draw full path
            mazeRenderer.drawAIPath(bfsAIPath, bfsPathColor);
            mazeRenderer.drawAIPath(dfsAIPath, dfsPathColor);
            mazeRenderer.drawAIPath(astarAIPath, astarPathColor);
        }

        if (redrawMaze) {
            maze.generate();
            mazeRenderer.createMazeTexture(wall, path, water, drawWater);

            bfsAI->findPath(maze, bfsStartX, bfsStartY, goalX, goalY);
            dfsAI->findPath(maze, dfsStartX, dfsStartY, goalX, goalY);
            astarAI->findPath(maze, astarStartX, astarStartY, goalX, goalY);

            bfsAnimator.reset(maze, bfsAI->getPath(), 1, 50);
            dfsAnimator.reset(maze, dfsAI->getPath(), 1, 50);
            astarAnimator.reset(maze, astarAI->getPath(), 1, 50);

            redrawMaze = false;
        }

        frames++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000) {
            fps = frames * 1000.0f / (currentTime - lastTime);
            window.updateFPSVisuals(fps);
            lastTime = currentTime;
            frames = 0;
        }

        window.swap();
    }
}
