#ifndef MAZE_AI_HPP
#define MAZE_AI_HPP

#include <vector>
#include <utility>

using namespace std;

class Maze;

class MazeAI {
public:
    virtual ~MazeAI() = default;

    virtual void findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) = 0;

    // Getters
    virtual const vector<pair<int, int>>& getPath() const = 0;
};

class DFS_AI : public MazeAI { 
private:
    vector<pair<int, int>> path;

public:
    DFS_AI() = default;
    ~DFS_AI() override = default;

    void findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) override;

    // Getters
    const vector<pair<int, int>>& getPath() const override;
};

class BFS_AI : public MazeAI {
private:
    vector<pair<int, int>> path;

public:
    BFS_AI() = default;
    ~BFS_AI() override = default;

    void findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) override;

    // Getters
    const vector<pair<int, int>>& getPath() const override;
};

#endif