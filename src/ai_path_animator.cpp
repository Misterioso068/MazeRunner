#include "program/ai_path_animator.hpp"
#include "program/maze.hpp"

PathAnimator::PathAnimator(const Maze& maze, const vector<pair<int, int>>& path, 
                           Uint32 baseDelay, Uint32 waterDelay) {
    timeOld = SDL_GetTicks();
    index = 0;
    populateDelays(maze, path, baseDelay, waterDelay);
}

void PathAnimator::update() {
    if (index >= delays.size()) return;

    Uint32 now = SDL_GetTicks();
    if (now - timeOld >= delays[index]) {
        index++;
        timeOld = now;
    }
}

void PathAnimator::reset(const Maze& maze, const vector<pair<int, int>>& path,
                         Uint32 baseDelay, Uint32 waterDelay) {
    index = 0;
    timeOld = SDL_GetTicks();
    populateDelays(maze, path, baseDelay, waterDelay);
}

void PathAnimator::populateDelays(const Maze& maze, const vector<pair<int,int>>& path, Uint32 baseDelay, Uint32 waterDelay) {
    const auto& grid = maze.getGrid();
    delays.clear();
    delays.reserve(path.size());

    for (auto [x, y] : path) {
        delays.push_back(grid[y][x].water ? waterDelay : baseDelay);
    }
}
