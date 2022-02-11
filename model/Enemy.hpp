#pragma once

#include <map>
#include "WorldCoordinates.h"
#include <Entity.h>
#include <GameLogicConst.h>

class Enemy : public Entity {
    public:
    float speed = 0.f;

    private:
    EnemyState state;
    EnemyStats stats;
    int targetPlayer = -1;
    float targetX = 0;
    Enemy(EntityType type, WorldCoordinates coords) :
            Entity(type, coords) {
        stats = INIT_ENEMY_STATS.at(type);
    }

    public:
    static Enemy* getZombie(WorldCoordinates coords);
    static Enemy* getIceberg(WorldCoordinates coords);

    float getHealth() { return stats.health; }
    float getArmor() { return stats.armor; }

    void target(int player_number);
    void target(float x);
    void lose_target();
};
