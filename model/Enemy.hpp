#pragma once

#include <map>
#include "WorldCoordinates.h"
#include <Entity.h>
#include <GameLogicConst.h>

class Model;

class Enemy : public Entity {
private:
    EnemyState state = EnemyState::Idle;
    float health;

    //EnemyStats stats;
    EnemyTarget target;
    float missing_target_player_for_seconds = 0;


    Enemy(EntityType type, WorldCoordinates coords) :
            Entity(type, coords) {
        //stats = INIT_ENEMY_STATS.at(type);
    }

    public:
    static Enemy* getZombie(WorldCoordinates coords);
    static Enemy* getIceberg(WorldCoordinates coords);

    float getHealth() const { return health; }
    void setHealth(const float health) { this->health = health; }

    //float getHealth() { return stats.health; }
    //float getArmor() { return stats.armor; }

    void targetPlayer(int player_number);
    void targetFixedX(float x);
    void lose_target();
    void doTargetUpdates(Model* model, float deltaT);
};
