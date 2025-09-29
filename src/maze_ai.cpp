#include <queue>
#include <stack>
#include <algorithm>
#include <memory>
#include "program/maze_ai.hpp"
#include "program/maze.hpp"

struct Node {
    int x, y;
    int g;
    int h;
    int f;
    shared_ptr<Node> parent;

    Node(int x, int y, int g, int h, shared_ptr<Node> parent = nullptr) 
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {} 
};

// Custom compare function for priotery queue (min-heap on f)
struct Compare {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
    if (a->f == b->f) return a->h > b->h; // prefer closer to goal if f equal
        return a->f > b->f;
    }
};

/*
    A_STAR_AI class implementation
*/
void A_STAR_AI::findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) {
    path.clear();

    const auto& grid = maze.getGrid();
    const int r = maze.getGridRows();
    const int c = maze.getGridCols();

    // Track the shortest known cost to each cell
    vector<vector<int>> gScore(r, vector<int>(c, INT_MAX));
    gScore[startY][startX] = 0;

    // Heuristic: Manhattan distance
    auto heuristic = [&](int x, int y) {
        return abs(x - goalX) + abs(y - goalY);
    };
    
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;

    auto start = make_shared<Node>(startX, startY, 0, heuristic(startX, startY));
    pq.push(start);

    shared_ptr<Node> goalNode = nullptr;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();

        // Goal reached
        if (cur->x == goalX && cur->y == goalY) {
            goalNode = cur;
            break;
        }

        // Explore neighbors
        for (auto [dx, dy] : directions) {
            int nx = cur->x + dx;
            int ny = cur->y + dy;

            if (nx >= 0 && nx < c && ny >= 0 && ny < r) {
                if (!grid[ny][nx].wall) {
                    int newG = cur->g + 1;

                    // Only consider this neighbor if we found a better path
                    if (newG < gScore[ny][nx]) {
                        gScore[ny][nx] = newG;
                        auto neighbor = make_shared<Node>(nx, ny, newG, heuristic(nx, ny), cur);
                        pq.push(neighbor);
                    }
                }
            }
        }
    }

    // Reconstruct path
    if (goalNode) {
        for (auto cur = goalNode; cur != nullptr; cur = cur->parent) {
            path.push_back({cur->x, cur->y});
        }
        reverse(path.begin(), path.end());
    }
}

const vector<pair<int, int>>& A_STAR_AI::getPath() const {
    return path;
}

/*
    BFS_AI class implementation
*/
void BFS_AI::findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) {
    path.clear();

    const auto& grid = maze.getGrid();
    const int r = maze.getGridRows();
    const int c = maze.getGridCols();

    vector<vector<bool>> visited(r, vector<bool>(c, false));
    vector<vector<pair<int, int>>> parent(r, vector<pair<int, int>>(c, {-1, -1}));

    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startY][startX] = true;

    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

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

        for (auto [dx, dy] : directions) {
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
void DFS_AI::findPath(const Maze& maze, int startX, int startY, int goalX, int goalY) {
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