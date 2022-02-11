#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Entity.h"
#include <map>
#include <Model.h>
#include <PlayerLogic.h>
#include <AttackState.hpp>
#include <FloorThing.hpp>
#include <GameLogicConst.h>
#include <Portal.hpp>

class GameLogic {
    private:
    Model* model;
    std::vector<PlayerLogic*> playerLogic;
    std::map<EntityType, float> enemySpawnCooldown;

    public:
    GameLogic(Model* model);
    void update(float elapsedTime);
    void move_player(int player, int x_sign, bool retreat, int z_sign, bool attack);
    int nPlayers();

    private:
    void updateEnemies(float elapsedTime);
    void spawnEnemy(EntityType type, float elapsedTime);
    bool isEnemyTooFarAway(Enemy* enemy);
    void killEnemy(Enemy* enemy);

    void updateFloorThings(float elapsedTime);
    void maybeSpawnPortal();
    void killPortal(FloorThing* portal);

    void handlePlayerCollisions(PlayerLogic* playerLogic, float elapsedTime);
};

#endif /* GAMELOGIC_H */
