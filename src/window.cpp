#include <iostream>
#include "program/window.hpp"
#include "program/maze.hpp"
#include "program/maze_ai.hpp"

Window::Window(const char* name, const int w, const int h) : name(name), width(w), height(h) {}

Window::~Window() {
    SDL_GL_DestroyContext(this->glContext);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

bool Window::init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Failed to initialize SDL3 video: " << SDL_GetError() << endl;
        return false;
    }

    this->window = SDL_CreateWindow(this->name, this->width, this->height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (this->window == NULL) {
        cout << "Failed to initialize SDL3 window: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    this->glContext = SDL_GL_CreateContext(this->window);
    if (this->glContext == NULL) {
        cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return false;
    }

    glewExperimental = true;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        cout << "Failed to initialize GLEW: " << glewGetErrorString(glewStatus) << endl;
        SDL_GL_DestroyContext(this->glContext);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return false;
    }

    glViewport(0, 0, width, height);

    return true;
}

void Window::swap() {
    SDL_GL_SwapWindow(this->window);
}

bool Window::handleEvents(bool& drawPath, bool& redrawMaze) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (SDL_EVENT_QUIT == event.type) {
            return false;
        }
        else if (SDL_EVENT_KEY_DOWN == event.type) {
            if (SDLK_ESCAPE == event.key.key) {
                return false;
            }
            else if (SDLK_R == event.key.key) {
                redrawMaze = true;
            }
            else if (SDLK_X == event.key.key) {
                drawPath = true;
            }
            else if (SDLK_C == event.key.key) {
                drawPath = false;
            }
        }
    }

    return true;
}