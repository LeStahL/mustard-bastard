#include <cstdlib>
#include "WorldCoordinates.h"
#include <helpers.h>

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

void WorldCoordinates::applyAcceleration(float _x_acc, float _y_acc, bool stop_first) {
    if (stop_first) {
        x_speed = 0;
        y_speed = 0;
        x_acc = 0;
        y_acc = 0;
    }
    x_speed += _x_acc;
    y_speed += _y_acc;
    y_acc = 10;
};

void WorldCoordinates::mightTurnAroundForTarget(float target_x) {
    if (sgn(x_speed) != sgn(target_x - x)) {
        x_speed = 0;
        facing_left ^= true;
    }
};

WorldCoordinates WorldCoordinates::RandomPositionOutside(float distance) {
    float x = rand() % 2 == 0 ? -distance : WIDTH + distance;
    int z = rand() % Z_PLANES;
    bool upWorld = rand() % 2 == 0;
    WorldCoordinates result(x, z, upWorld);
    result.facing_left = x > WIDTH;
    return result;
}
