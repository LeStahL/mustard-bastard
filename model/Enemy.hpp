#pragma once

#include <IsDrawable.hpp>

enum EnemyType {
    ZombieAndCat,
    IcebergAndFairy
};

class Enemy : public IsDrawable {
    private:
    EnemyType type;

    public:
    float health = 0;
    float speed = 0;

    Enemy(int graphicId, EnemyType type, WorldPosition position);
};
