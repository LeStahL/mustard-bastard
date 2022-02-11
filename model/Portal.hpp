#pragma once

#include <FloorThing.hpp>
#include <GameLogicConst.h>

class Portal : public FloorThing {
    // hack: just make everything public so we can pfriemel around in it
    public:
    float size = PORTAL_EPSILON_SIZE;
    bool spawning = true;
    float lifetime = 0;
    bool used = false;

    Portal(WorldCoordinates position) : FloorThing(position) {
    };

    float getHalfWidth() { return size * PORTAL_MAX_HALFWIDTH; }

    std::pair<float, float> getCollisionXInterval() override {
        float halfWidth = getHalfWidth();
        return std::pair(coords.x - halfWidth, coords.x + halfWidth);
    }

    bool canCollide() override {
        return !spawning && lifetime > 0 && !used;
    }

    void shutDown() {
        used = true;
        spawning = false;
        lifetime = 0;
    }
};
