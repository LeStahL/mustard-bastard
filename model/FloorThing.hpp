#pragma once

#include <Entity.h>

class FloorThing : public Entity {
    public:
    FloorThing(WorldPosition position) : Entity(position) {};
};
