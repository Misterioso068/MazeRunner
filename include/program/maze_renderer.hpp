#ifndef MAZE_RENDERER_HPP
#define MAZE_RENDERER_HPP

#include <vector>
#include <utility>

using namespace std;

class Maze;

class MazeRenderer {
private:
    Maze& maze;
    GLfloat cellSize;

    void drawCell(int x, int y);

public:
    MazeRenderer(Maze& maze, GLfloat cellSize);
    ~MazeRenderer();

    void drawMaze();
    void drawAIPath(const vector<pair<int, int>>& path);
    void drawPlayer();

    void updateProjection();
    void updateCellSize(GLfloat newCellSize);
};

#endif