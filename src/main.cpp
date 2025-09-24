#include <iostream>
#include <SDL3/SDL.h>
#include <GL/glew.h>

using namespace std;

typedef struct {
    int row, col;
    bool visited = false;
    bool wall = true;
} Cell;

int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Failed to initialize SDL3 video: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Maze Runner", 800, 450, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (window == NULL) {
        cout << "Failed to initialize SDL3 window: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) {
        cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glewExperimental = true;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK) {
        cout << "Failed to initialize GLEW: " << glewGetErrorString(glewStatus) << endl;
        SDL_GL_DestroyContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool run = true;
    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (SDL_EVENT_QUIT == event.type) {
                run = false;
            }
            else if (SDL_EVENT_KEY_DOWN == event.type) {
                if (SDLK_ESCAPE == event.key.key) {
                    run = false;
                }
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}