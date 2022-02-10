#pragma once

#include <map>
#include <Entity.h>
#include <gamelogic_const.h>

class FloorThing : public Entity {
    public:
    FloorThing(WorldPosition position) : Entity(position) {};

    void endLife();
};

class Portal : public FloorThing {
    // hack: just make everything public so we can pfriemel around in it
    public:
    float size = PORTAL_EPSILON_SIZE;
    bool spawning = true;
    float lifetime = 0;

    Portal(WorldPosition position) : FloorThing(position) { };
};
