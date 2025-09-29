#include "program/ai_path_animator.hpp"

PathAnimator::PathAnimator(size_t size, Uint32 delay) : pathSize(size), timeOld(0), stepDelay(delay), index(0) {}

void PathAnimator::update() {
    Uint32 now = SDL_GetTicks();
    if (index < pathSize && now - timeOld >= stepDelay) {
        index++;
        timeOld = now;
    }
}

void PathAnimator::reset(size_t newSize) {
    pathSize = newSize;
    index = 0;
    timeOld = 0;
}