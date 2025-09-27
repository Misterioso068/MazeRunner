#include <queue>
#include <stack>
#include <algorithm>
#include "program/maze_ai.hpp"
#include "program/maze.hpp"

/*
    BFS_AI class implementation
*/
void BFS_AI::findPath(const Maze& maze, const int startX, const int startY, const int goalX, const int goalY) {
    path.clear();

    const auto& grid = maze.getGrid();
    const int r = maze.getGridRows();
    const int c = maze.getGridCols();

    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<vector<pair<int, int>>> parent(r, vector<pair<int, int>>(c, {-1, -1}));

    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == goalX && y == goalY) {
            // Reconstruct path
            for (pair<int, int> cur = {x, y}; cur.first != -1; cur = parent[cur.second][cur.first]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());
            return;
        }

        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < c && ny >= 0 && ny < r) {
                if (!visited[ny][nx] && !grid[ny][nx].wall) {
                    visited[ny][nx] = true;
                    parent[ny][nx] = {x, y};
                    q.push({nx, ny});
                }
            }
        }

    }
}

const vector<pair<int, int>>& BFS_AI::getPath() const {
    return path;
}

/*
    DFS_AI class implementaion
*/
void DFS_AI::findPath(const Maze& maze, const int startX, const int startY, const int goalX, const int goalY) {
    path.clear();

    const auto& grid = maze.getGrid();
    const int r = maze.getGridRows();
    const int c = maze.getGridCols();

    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<vector<pair<int, int>>> parent(r, vector<pair<int, int>>(c, {-1, -1}));

    stack<pair<int, int>> s;
    s.push({startX, startY});
    visited[startY][startX] = true;

    const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!s.empty()) {
        auto [x, y] = s.top();
        s.pop();

        if (x == goalX && y == goalY) {
            // Reconstruct path
            for (pair<int, int> cur = {x, y}; cur.first != -1; cur = parent[cur.second][cur.first]) {
                path.push_back(cur);
            }
            reverse(path.begin(), path.end());
            return;
        }

        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < c && ny >= 0 && ny < r) {
                if (!visited[ny][nx] && !grid[ny][nx].wall) {
                    visited[ny][nx] = true;
                    parent[ny][nx] = {x, y};
                    s.push({nx, ny});
                }
            }
        }
    }
}

const vector<pair<int, int>>& DFS_AI::getPath() const {
    return path;
}