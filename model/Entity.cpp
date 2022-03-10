#include <Entity.hpp>
#include <cmath>

int Entity::id_counter = 0;

EntityType Entity::getType() {
    return type;
}

std::pair<float, float> Entity::getCollisionXInterval() {
    return std::pair(coords.x - 1, coords.x + 1);
}

bool Entity::canCollide() {
    return true;
}

void Entity::doCoordUpdates(float deltaT) {
    if (fabs(coords.x_speed) < 1e-3) {
        coords.x_speed = 0;
    } else {
        coords.facing_left = coords.x_speed < 0;
    }
    coords.doPhysicalUpdates(deltaT);
}
