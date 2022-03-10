#pragma once

#include <FloorThing.hpp>
#include <GameLogicConst.hpp>

class Portal : public FloorThing {
    // hack: just make everything public so we can pfriemel around in it
    public:
    float size = PORTAL_EPSILON_SIZE;
    bool spawning = true;
    float lifetime = 0;
    bool used = false;

    public:
    Portal(WorldCoordinates position);
    float getHalfWidth();
    void shutDown();

    std::pair<float, float> getCollisionXInterval() override;
    bool canCollide() override;
};
