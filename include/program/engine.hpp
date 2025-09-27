#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "program/window.hpp"
#include "program/maze.hpp"
#include "program/maze_renderer.hpp"
#include "program/maze_ai.hpp"

using namespace std;

class Engine {
private:
    Window window;
    Maze maze;
    MazeRenderer mazeRenderer;
    MazeAI ai;

    bool running;
    bool drawPath;

public:
    Engine(int width, int height, int rows, int cols, int cellSize, double loopChance);
    void run();  // main game loop
};

#endif
