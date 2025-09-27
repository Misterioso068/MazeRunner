#ifndef MAZE_AI_HPP
#define MAZE_AI_HPP

#include <vector>
#include <utility>

using namespace std;

class Maze;

class MazeAI {
private:
    vector<pair<int, int>> path;

public:
    MazeAI();
    ~MazeAI();

    void BFSAIPathfinding(const Maze& maze, const int startX, const int startY, const int goalX, const int goalY);

    // Getters
    const vector<pair<int, int>>& getAIPath() const {return path;}
};

#endif