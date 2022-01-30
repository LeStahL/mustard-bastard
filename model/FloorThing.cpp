#include <FloorThing.hpp>

FloorThing::FloorThing(FloorThingType type, WorldPosition position) :
        IsDrawable(position), type(type) {
    // could switch type here, i.e. Portals should be a primitive, but Medikit have a sprite.
}