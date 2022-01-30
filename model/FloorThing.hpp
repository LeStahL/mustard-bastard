#pragma once

#include <map>
#include <IsDrawable.hpp>

enum FloorThingType {
    Portal,
    // Medikit,
    // etc.
};

class FloorThing : public IsDrawable {
    private:
    FloorThingType type;

    public:
    FloorThing(FloorThingType type, WorldPosition position);
};
