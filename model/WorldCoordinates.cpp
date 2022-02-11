#include "WorldCoordinates.h"

WorldCoordinates::WorldCoordinates(float x, int z, bool upWorld) :
    x(x),
    z(z),
    upWorld(upWorld) {
}

void WorldCoordinates::toggleWorld() {
    upWorld = !upWorld;
}

bool WorldCoordinates::collides_with(WorldCoordinates other) {
    if (other.z != z || other.upWorld != upWorld)
        return false;

    auto other_left = other.x - other.collision_width;
    auto other_right = other.x + other.collision_width;
    auto left = x - collision_width;
    auto right = x + collision_width;
    return (right > other_left && right <= other_right)
        || (left < other_right && left >= other_left);
}

void WorldCoordinates::doPhysicalUpdates(float deltaT) {
    x_speed += x_acc * deltaT;
    x += x_speed * deltaT;

    y_speed += y_acc * deltaT;
    y += y_speed * deltaT;

    // it's just the ground, innit
    if (y < 0) {
        y = 0;
        y_speed = 0;
    }
}