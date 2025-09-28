#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <utility>

using namespace std;

struct Cell {
    int row;
    int col;
    bool visited;
    bool wall;

    Cell() : row(0), col(0), visited(false), wall(true) {}
    Cell(int r, int c, bool v, bool w) : row(r), col(c), visited(v), wall(w) {}
};

class Maze {
private:
    int ROWS, COLS;
    double LOOPCHANCE;
    int GRIDROWS, GRIDCOLS;
    vector<vector<Cell>> grid;

    void shuffleDirs(vector<pair<int, int>>& d);
    void createGridLayout();
    void carveMazeRecursively(int x, int y);
    void carveMazeIteratively(int x, int y);

public:
    Maze(int rows, int cols, double loopChance);
    ~Maze();

    void generate();
    void changeLoopChance(double loopChance);

    // Getters
    const vector<vector<Cell>>& getGrid() const {return grid;};
    int getGridRows() const {return GRIDROWS;};
    int getGridCols() const {return GRIDCOLS;};
};

#endif