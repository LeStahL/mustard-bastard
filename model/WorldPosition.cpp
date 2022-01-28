#include "WorldPosition.h"

WorldPosition::WorldPosition(float x, int z, bool upWorld) :
    x(x),
    z(z),
    upWorld(upWorld) {
}

void WorldPosition::toggleWorld() {
    upWorld != upWorld;
}