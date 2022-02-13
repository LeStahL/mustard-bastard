#pragma once

#include <FloorThing.hpp>

class Medikit : public FloorThing {
    public:
    bool spawning = true;

    Medikit(WorldCoordinates coords) : FloorThing(EntityType::Medikit, coords) {};

    bool canCollide() override;
};
