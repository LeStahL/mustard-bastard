#pragma once

#include "WorldCoordinates.h"
#include <map>
#include <Entity.h>

class FloorThing : public Entity {
    public:
    FloorThing(WorldCoordinates coords) : Entity(EntityType::Portal, coords) {};
};
