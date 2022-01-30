#pragma once

#include <map>
#include <Entity.h>

enum FloorThingType {
    Portal,
    // Medikit,
    // etc.
};

class FloorThing : public Entity {
    private:
    FloorThingType type;

    public:
    FloorThing(FloorThingType type, WorldPosition position);
};
