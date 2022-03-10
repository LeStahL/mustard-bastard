#pragma once

#include <map>

#include <WorldCoordinates.hpp>
#include <Entity.hpp>

class FloorThing : public Entity {
    public:
    FloorThing(EntityType type, WorldCoordinates coords) : Entity(type, coords) {};
};
