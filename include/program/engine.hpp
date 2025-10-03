#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "program/window.hpp"
#include "program/maze.hpp"
#include "program/maze_renderer.hpp"
#include "program/maze_ai.hpp"
#include "program/ai_path_animator.hpp"
#include "program/camera2D.hpp"

using namespace std;

class Engine {
private:
    Maze maze;
    MazeRenderer mazeRenderer;
    Window window;

    bool running;
    bool drawPath;
    bool beginAnimation;
    bool drawWater;
    bool toggleWater;
    bool redrawMaze;

public:
    Engine(int width, int height, int rows, int cols, int cellSize, double loopChance, double waterChance);
    void run();  // main game loop
};

#endif
