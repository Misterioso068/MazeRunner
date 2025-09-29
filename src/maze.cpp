#include <random>
#include <algorithm>
#include <stack>
#include "program/maze.hpp"

Maze::Maze(const int rows, const int cols, double loopChance, double waterChance) 
    : ROWS(rows), 
      COLS(cols), 
      LOOPCHANCE(loopChance),
      WATERCHANCE(waterChance),
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
    carveMazeIteratively(1, 1);
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
                    grid[i][j] = Cell{i, j, false, true, false};
                }
                else {
                    grid[i][j] = Cell{i, j, false, false, false};
                }
            }
            else {
                grid[i][j] = Cell{i, j, false, true, false};
            }
            
        }
    }
}

void Maze::carveMazeRecursively(int x, int y) {
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
                carveMazeRecursively(nx, ny);
            }
            else if (rand() % 100 < LOOPCHANCE * 100) {
                // With some probabilty carve into the already visited neighbor so that we have loops/escape routes
                grid[y + dy/2][x + dx/2].wall = false;
            }
        }
    }
}

void Maze::carveMazeIteratively(int x, int y) {
    grid[y][x].wall = false;

    vector<vector<bool>> visited(GRIDROWS, vector<bool>(GRIDCOLS, false));

    stack<pair<int, int>> s;
    s.push({x, y});
    visited[y][x] = true;

    while (!s.empty()) {
        auto [x, y] = s.top();
        s.pop();

        vector<pair<int,int>> dirs = {{2,0}, {-2,0}, {0,2}, {0,-2}};
        shuffleDirs(dirs);

        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < GRIDCOLS && ny >= 0 && ny < GRIDROWS) {
                if (!visited[ny][nx]) {
                    // Knock down the wall *between* (x,y) and (nx,ny)
                    grid[y + dy/2][x + dx/2].wall = false;
                    visited[y + dy/2][x + dx/2] = true;
                    visited[ny][nx] = true;

                    if (rand() % 100 < WATERCHANCE * 100) {
                        // With some probabilty make the block water
                        grid[y + dy/2][x + dx/2].water = true;
                    }

                    s.push({x, y});
                    s.push({nx, ny});
                    break;
                }
                else if (rand() % 100 < LOOPCHANCE * 100) {
                    // With some probabilty carve into the already visited neighbor so that we have loops/escape routes
                    grid[y + dy/2][x + dx/2].wall = false;
                }
            }
        }
    }
}