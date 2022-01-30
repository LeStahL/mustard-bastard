#include "WorldPosition.h"

WorldPosition::WorldPosition(float x, int z, bool upWorld) :
    x(x),
    z(z),
    upWorld(upWorld) {
}

void WorldPosition::toggleWorld() {
    upWorld = !upWorld;
}

bool WorldPosition::collides_with(WorldPosition other) {
    if (other.z != z || other.upWorld != upWorld)
        return false;

    auto other_left = other.x - other.collision_width;
    auto other_right = other.x + other.collision_width;
    auto left = x - collision_width;
    auto right = x + collision_width;
    return (right > other_left && right <= other_right)
        || (left < other_right && left >= other_left);
}
