#include <Entity.h>

int Entity::id_counter = 0;

std::pair<float, float> Entity::getCollisionXInterval() {
    return std::pair(position.x - 1, position.x + 1);
}

bool Entity::isCollisionActive() {
    return true;
}
