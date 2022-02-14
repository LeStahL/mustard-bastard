#pragma once

#include <FloorThing.hpp>

class Medikit : public FloorThing {
    public:
    bool spawning = false;
    bool wasUsed = false;

    Medikit(WorldCoordinates coords) : FloorThing(EntityType::Medikit, coords) {};

    float width();
    bool canCollide() override;
};
