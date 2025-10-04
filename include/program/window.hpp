#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <GL/glew.h>
#include "program/camera2D.hpp"

using namespace std;

class Maze;
class MazeAI;

class Window {
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    const char* name;
    int width;
    int height;
    int mazeContainerWidth;
    int mazeContainerHeight;

    bool draggingMouse;
    GLfloat lastMouseX;
    GLfloat lastMouseY;
    GLfloat mouseSens;

    void updateViewport();

public:
    Window(const char* name, const int w, const int h, const int mazeWidth, const int mazeHeight);
    ~Window();

    bool init();
    void swap();
    bool handleEvents(bool& drawPath, bool& redrawMaze, bool& beginAnimation, bool& toggleWater, Camera2D& cam);
    void updateFPSVisuals(GLfloat fps);
};

#endif