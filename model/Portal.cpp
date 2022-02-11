#include <Portal.hpp>

Portal::Portal(WorldCoordinates position) :
    FloorThing(EntityType::Portal, position) {
}

float Portal::getHalfWidth() {
    return size * PORTAL_MAX_HALFWIDTH;
}

void Portal::shutDown() {
    used = true;
    spawning = false;
    lifetime = 0;
}

std::pair<float, float> Portal::getCollisionXInterval() {
    float halfWidth = getHalfWidth();
    return std::pair(coords.x - halfWidth, coords.x + halfWidth);
}
bool Portal::canCollide() {
    return !spawning && lifetime > 0 && !used;
}
