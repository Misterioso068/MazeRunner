#ifndef MAZE_RENDERER_HPP
#define MAZE_RENDERER_HPP

#include <vector>
#include <utility>

using namespace std;

class Maze;

struct Color {
    GLfloat r, g, b;
};

class MazeRenderer {
private:
    Maze& maze;
    GLfloat cellSize;

    void drawCell(int x, int y);

public:
    MazeRenderer(Maze& maze, GLfloat cellSize);
    ~MazeRenderer();

    void drawMaze(const Color& wall, const Color& path, const Color& water, bool drawWater);
    void drawAIPath(const vector<pair<int, int>>& path, const Color& c);
    void drawAIPathAnimated(const vector<pair<int, int>>& path, size_t index, const Color& c);
    void drawPlayer(const Color& c);

    void updateProjection();
    void updateCellSize(GLfloat newCellSize);
};

#endif