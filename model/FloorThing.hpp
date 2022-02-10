#pragma once

#include <map>
#include <Entity.h>
#include <GameLogicConst.h>

class FloorThing : public Entity {
    public:
    FloorThing(WorldPosition position) : Entity(position) {};
};

class Portal : public FloorThing {
    // hack: just make everything public so we can pfriemel around in it
    public:
    float size = PORTAL_EPSILON_SIZE;
    bool spawning = true;
    float lifetime = 0;

    Portal(WorldPosition position) : FloorThing(position) {
    };

    float getHalfWidth() { return size * PORTAL_MAX_HALFWIDTH; }
};
