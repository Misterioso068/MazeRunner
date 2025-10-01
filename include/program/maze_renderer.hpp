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
    GLuint mazeTexture;

    void drawCell(int x, int y);

public:
    MazeRenderer(Maze& maze, GLfloat cellSize);
    ~MazeRenderer();

    // Prevent copying of MazeRenderer so that gpu leak does not occur with double freeing mazeTexture
    MazeRenderer(const MazeRenderer&) = delete;
    MazeRenderer& operator = (const MazeRenderer&) = delete;

    // Allow moving MazeRenderer to new variable
    MazeRenderer(MazeRenderer&& other) noexcept;
    MazeRenderer& operator=(MazeRenderer&& other) noexcept;

    void createMazeTexture(const Color& wall, const Color& path, const Color& water, bool drawWater);
    void drawMaze();
    void drawAIPath(const vector<pair<int, int>>& path, const Color& c);
    void drawAIPathAnimated(const vector<pair<int, int>>& path, size_t index, const Color& c);
    void drawPlayer(const Color& c);

    void updateCellSize(GLfloat newCellSize);
};

#endif