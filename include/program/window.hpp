#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include <GL/glew.h>

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

public:
    Window(const char* name, const int w, const int h);
    ~Window();

    bool init();
    void swap();
    bool handleEvents(Maze& maze, MazeAI& ai, bool& drawPath);

};

#endif