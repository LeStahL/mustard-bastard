#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Entity.h"
#include <map>
#include <Model.h>
#include <PlayerLogic.h>
#include <AttackState.hpp>
#include <FloorThing.hpp>
#include <GameLogicConst.h>
#include <Medikit.hpp>

class GameLogic {
    private:
    Model* model;
    std::vector<PlayerLogic*> playerLogic;
    std::map<EntityType, float> enemySpawnCooldown;

    public:
    GameLogic(Model* model);
    void init();
    void update(float elapsedTime);
    void move_player(int player, int x_sign, bool retreat, int z_sign, bool attack);
    int nPlayers();
    void pauseGame();
    void resumeGame();

    private:
    void updateEnemies(float elapsedTime);
    void spawnEnemy(EntityType type, float elapsedTime);
    bool isEnemyTooFarAway(Enemy* enemy);
    void killEnemy(Enemy* enemy);

    void updateFloorThings(float elapsedTime);
    void maybeSpawnFloorThing(EntityType type);

    void updateMedikit(Medikit *medikit, float time);

    void handlePlayerCollisions(PlayerLogic* playerLogic, float elapsedTime);

};

#endif /* GAMELOGIC_H */
