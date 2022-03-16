#pragma once

#include <random>

class Interval {
private:
    float min;
    float max;

public:
    Interval(float min, float max) : min(min), max(max) {}

    float getMin() const { return min; }
    float getMax() const { return max; }

    float getUniformRandom() const {
        int draw = rand() % 1000;
        return min + (max - min) * 1e-3 * draw;
    }

    bool contains(const float value) const {
        return value >= min && value <= max; // assume we got a closed intervall
    }

};
