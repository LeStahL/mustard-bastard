#include <Entity.h>

int Entity::id_counter = 0;

EntityType Entity::getType() {
    return type;
}

std::pair<float, float> Entity::getCollisionXInterval() {
    return std::pair(position.x - 1, position.x + 1);
}

bool Entity::canCollide() {
    return true;
}
