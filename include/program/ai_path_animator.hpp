#ifndef AI_PATH_ANIMATOR_HPP
#define AI_PATH_ANIMATOR_HPP

#include <SDL3/SDL.h>
#include <vector>
#include <utility>

using namespace std;

class Maze;

class PathAnimator {
private:
    Uint32 timeOld;
    vector<Uint32> delays;
    size_t index;

    void populateDelays(const Maze& maze, const vector<pair<int,int>>& path, Uint32 baseDelay, Uint32 waterDelay);

public:
    PathAnimator(const Maze& maze, const vector<pair<int, int>>& path, Uint32 baseDelay = 200, Uint32 waterDelay = 400);

    void update();
    size_t getIndex() const {return index;};
    void reset(const Maze& maze, const vector<pair<int, int>>& path, Uint32 baseDelay = 200, Uint32 waterDelay = 400);
};

#endif