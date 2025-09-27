#include <random>
#include <algorithm>
#include "program/maze.hpp"

Maze::Maze(const int rows, const int cols, double loopChance) 
    : ROWS(rows), 
      COLS(cols), 
      LOOPCHANCE(loopChance),
      GRIDROWS(2 * rows + 1),
      GRIDCOLS(2 * cols + 1),
      grid(GRIDROWS, vector<Cell>(GRIDCOLS))
{
    generate();
}

Maze::~Maze() {
    // Clean up maze if needed
}

void Maze::generate() {
    createGridLayout();
    carveMaze(1, 1);
}

void Maze::changeLoopChance(double newLoopChance) {
    if (newLoopChance < 0.0) newLoopChance = 0.0;
    if (newLoopChance > 1.0) newLoopChance = 1.0;
    LOOPCHANCE = newLoopChance;
}

void Maze::shuffleDirs(vector<pair<int, int>>& d) {
    static random_device rd;
    static mt19937 g(rd());

    shuffle(d.begin(), d.end(), g);
}

void Maze::createGridLayout() {
    for (int i = 0; i < GRIDROWS; i++) {
        for (int j = 0; j < GRIDCOLS; j++) {
            if (i % 2 != 0) {
                if (j % 2 == 0) {
                    grid[i][j] = Cell{i, j, false, true};
                }
                else {
                    grid[i][j] = Cell{i, j, false, false};
                }
            }
            else {
                grid[i][j] = Cell{i, j, false, true};
            }
            
        }
    }
}

void Maze::carveMaze(int x, int y) {
    grid[y][x].visited = true;
    grid[y][x].wall = false;

    vector<pair<int,int>> dirs = {{2,0}, {-2,0}, {0,2}, {0,-2}};
    shuffleDirs(dirs);

    for (auto [dx, dy] : dirs) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < GRIDCOLS && ny >= 0 && ny < GRIDROWS) {
            if (!grid[ny][nx].visited) {
                // Knock down the wall *between* (x,y) and (nx,ny)
                grid[y + dy/2][x + dx/2].wall = false;
                carveMaze(nx, ny);
            }
            else if (rand() % 100 < LOOPCHANCE * 100) {
                // With some probabilty carve into the already visited neighbor so that we have loops/escape routes
                grid[y + dy/2][x + dx/2].wall = false;
            }
        }
    }
}