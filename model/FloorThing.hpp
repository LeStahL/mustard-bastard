#pragma once

#include "WorldCoordinates.h"
#include <map>
#include <Entity.h>

class FloorThing : public Entity {
    public:
    FloorThing(EntityType type, WorldCoordinates coords) : Entity(type, coords) {};
};
