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
    bool water;

    Cell() : row(0), col(0), visited(false), wall(true), water(false){}
    Cell(int r, int c, bool v, bool w, bool wtr) : row(r), col(c), visited(v), wall(w), water(wtr) {}
};

class Maze {
private:
    int ROWS, COLS;
    double LOOPCHANCE, WATERCHANCE;
    int GRIDROWS, GRIDCOLS;
    vector<vector<Cell>> grid;

    void shuffleDirs(vector<pair<int, int>>& d);
    void createGridLayout();
    void carveMazeRecursively(int x, int y);
    void carveMazeIteratively(int x, int y);

public:
    Maze(int rows, int cols, double loopChance, double waterChance);
    ~Maze();

    void generate();
    void changeLoopChance(double loopChance);

    // Getters
    const vector<vector<Cell>>& getGrid() const {return grid;};
    int getGridRows() const {return GRIDROWS;};
    int getGridCols() const {return GRIDCOLS;};
};

#endif