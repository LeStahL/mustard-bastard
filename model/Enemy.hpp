#pragma once

#include "WorldPosition.h"
#include <Entity.h>

class Enemy : public Entity {
    public:
    float health = 0;
    float speed = 100.0f;

    private:
    Enemy(EntityType type, WorldPosition position) :
            Entity(type, position) {}

    public:
    static Enemy* getZombie(WorldPosition position);
    static Enemy* getIceberg(WorldPosition position);
};
