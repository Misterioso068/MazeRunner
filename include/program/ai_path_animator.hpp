#ifndef AI_PATH_ANIMATOR_HPP
#define AI_PATH_ANIMATOR_HPP

#include <SDL3/SDL.h>
#include <vector>
#include <utility>

using namespace std;

class PathAnimator {
private:
    size_t pathSize;
    Uint32 timeOld;
    Uint32 stepDelay;
    size_t index;

public:
    PathAnimator(size_t size, Uint32 delay);

    void update();
    size_t getIndex() const {return index;};
    void reset(size_t newSize);
};

#endif