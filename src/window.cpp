#include <iostream>
#include "program/window.hpp"
#include "program/maze.hpp"
#include "program/maze_ai.hpp"

Window::Window(const char* name, const int w, const int h) 
               : name(name), width(w), height(h), mazeContainerWidth(w), mazeContainerHeight(h), draggingMouse(false), lastMouseX(0), lastMouseY(0) {}

Window::~Window() {
    if (glContext) SDL_GL_DestroyContext(this->glContext);
    if (window) SDL_DestroyWindow(this->window);
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

    updateViewport();

    return true;
}

void Window::swap() {
    SDL_GL_SwapWindow(this->window);
}

void Window::updateViewport() {
    // Keep the maze container at the center of the window
    int offSetX = (width - mazeContainerWidth) / 2;
    int offSetY = (height - mazeContainerHeight) / 2; 

    glViewport(offSetX, offSetY, mazeContainerWidth, mazeContainerHeight);
}

bool Window::handleEvents(bool& drawPath, bool& redrawMaze, bool& beginAnimation, bool& toggleWater, Camera2D& cam) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (SDL_EVENT_QUIT == event.type) {
            return false;
        }
        else if (SDL_EVENT_WINDOW_RESIZED == event.type) {
            SDL_GetWindowSize(this->window, &this->width, &this->height);
            updateViewport();
        }
        else if (SDL_EVENT_MOUSE_BUTTON_DOWN == event.type) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                draggingMouse = true;
                lastMouseX = event.motion.x;
                lastMouseY = event.motion.y;
            }
        }
        else if (SDL_EVENT_MOUSE_BUTTON_UP == event.type) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                draggingMouse = false;
            }
        }
        else if (SDL_EVENT_MOUSE_MOTION == event.type) {
            if (draggingMouse) {
                GLfloat dx = event.motion.x - lastMouseX;
                GLfloat dy = event.motion.y - lastMouseY;

                cam.move(-dx * 5.0f/ cam.zoom, -dy * 5.0f/ cam.zoom); // 5.0f is mouse sensitivity

                lastMouseX = event.motion.x;
                lastMouseY = event.motion.y;
            }
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
            else if (SDLK_B == event.key.key) {
                beginAnimation = true;
            }
            else if (SDLK_N == event.key.key) {
                beginAnimation = false;
            }
            else if (SDLK_T == event.key.key) {
                toggleWater = true;
            }
            else if (SDLK_EQUALS == event.key.key) {
                cam.zoomIn();
            }
            else if (SDLK_MINUS == event.key.key) {
                cam.zoomOut();
            }
        }
    }

    return true;
}