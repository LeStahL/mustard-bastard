#pragma once

#include "WorldPosition.h"
#include <map>
#include <Entity.h>

class FloorThing : public Entity {
    public:
    FloorThing(WorldPosition position) : Entity(EntityType::Portal, position) {};
};
