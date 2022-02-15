#pragma once

#include <FloorThing.hpp>

class Medikit : public FloorThing {
    public:
    bool spawning = true;
    bool wasUsed = false;
    float x0 = 0.0f;

    Medikit(WorldCoordinates coords) : FloorThing(EntityType::Medikit, coords), x0(coords.x) {};

    float width();
    bool canCollide() override;
};
