#pragma once

#include <Entity.h>

enum EnemyType {
    ZombieAndCat,
    IcebergAndFairy
};

class Enemy : public Entity {
    public:
    EnemyType type;

    public:
    float health = 0;
    float speed = 100;

    Enemy(EnemyType type, WorldPosition position);
};
