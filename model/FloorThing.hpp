#pragma once

#include <map>
#include <Entity.h>

enum FloorThingType {
    Portal,
    // Medikit,
    // etc.
};

class FloorThing : public Entity {
    // hack: just make everything public so we can pfriemel around in it
    public:
    FloorThingType type;
    float size = 1;
    bool spawning = true;
    float lifetime = 0;

    FloorThing(FloorThingType type, WorldPosition position);
    void endLife();
};

FloorThing::FloorThing(FloorThingType type, WorldPosition position) :
        Entity(position), type(type) {
    // could switch type here, i.e. Portals should be a primitive, but Medikit have a sprite.
}
