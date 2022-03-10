#pragma once

#include <utility>
#include <cstdlib>

class Interval {

    public:
        float min;
        float max;

    Interval(float min, float max): min(min), max(max) {}

    float getUniformRandom() const {
        int draw = rand() % 1000;
        return min + (max - min) * 1e-3 * draw;
    }

};
