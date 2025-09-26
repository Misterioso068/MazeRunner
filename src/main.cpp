#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <SDL3/SDL.h>
#include <GL/glew.h>

using namespace std;

struct Cell {
    int row;
    int col;
    bool visited;
    bool wall;

    Cell() : row(0), col(0), visited(false), wall(true) {}
    Cell(int r, int c, bool v, bool w) : row(r), col(c), visited(v), wall(w) {}
};

void shuffleDirs(vector<pair<int, int>>& d) {
    static random_device rd;
    static mt19937 g(rd());

    shuffle(d.begin(), d.end(), g);
}

void DFSMazeGenerator(int x, int y, vector<vector<Cell>>& grid, int r, int c, double loopChance) {
    grid[y][x].visited = true;
    grid[y][x].wall = false;

    vector<pair<int,int>> dirs = {{2,0}, {-2,0}, {0,2}, {0,-2}};
    shuffleDirs(dirs);

    for (auto [dx, dy] : dirs) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < c && ny >= 0 && ny < r) {
            if (!grid[ny][nx].visited) {
                // Knock down the wall *between* (x,y) and (nx,ny)
                grid[y + dy/2][x + dx/2].wall = false;
                DFSMazeGenerator(nx, ny, grid, r, c, loopChance);
            }
            else if (rand() % 100 < loopChance * 100) {
                // With some probabilty carve into the already visited neighbor so that we have loops/escape routes
                grid[y + dy/2][x + dx/2].wall = false;
            }
        }
    }
}

void fillGrid(vector<vector<Cell>>& g, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i % 2 != 0) {
                if (j % 2 == 0) {
                    g[i][j] = Cell{i, j, false, true};
                }
                else {
                    g[i][j] = Cell{i, j, false, false};
                }
            }
            else {
                g[i][j] = Cell{i, j, false, true};
            }
            
        }
    }
}


int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Failed to initialize SDL3 video: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Maze Runner", 1000, 1000, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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

    const int CELL_SIZE = 10;
    const int ROWS = 10;
    const int COLS = 10;
    const int GRIDROWS = 2 * ROWS + 1;
    const int GRIDCOLS = 2 * COLS + 1;
    const double LOOPCHANCE = 0.02;

    vector<vector<Cell>> grid(GRIDROWS, vector<Cell>(GRIDCOLS));
    fillGrid(grid, GRIDROWS, GRIDCOLS);
    DFSMazeGenerator(1, 1, grid, GRIDROWS, GRIDCOLS, LOOPCHANCE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, GRIDCOLS * CELL_SIZE, GRIDROWS * CELL_SIZE, 0, -1, 1); // origin at top-left
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, 1000, 1000);

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
                else if (SDLK_R == event.key.key) {
                    //Redraw maze
                    fillGrid(grid, GRIDROWS, GRIDCOLS);
                    DFSMazeGenerator(1, 1, grid, GRIDROWS, GRIDCOLS, LOOPCHANCE);
                }
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < GRIDROWS; i++) {
            for (int j = 0; j < GRIDCOLS; j++) {
                if (grid[i][j].wall) {
                    glColor3f(0.3f, 0.3f, 0.3f); // darker grey
                } else {
                    glColor3f(1.0f, 1.0f, 1.0f); // white
                }

                float x = j * CELL_SIZE;
                float y = i * CELL_SIZE;

                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + CELL_SIZE, y);
                glVertex2f(x + CELL_SIZE, y + CELL_SIZE);
                glVertex2f(x, y + CELL_SIZE);
                glEnd();
            }
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}