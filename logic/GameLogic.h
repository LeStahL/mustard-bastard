#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <map>
#include <Model.h>
#include <AttackState.hpp>
#include <FloorThing.hpp>
#include <GameLogicConst.h>
#include <Portal.hpp>

class GameLogic {
    private:
    Model* model;
    std::map<EnemyType, float> enemySpawnCooldown;

    const std::map<Weapon, double> ATTACK_COOLDOWN = {
        {Weapon::Hand, 500.},
        {Weapon::Axe, 2000.},
        {Weapon::Mustard, 1000.},
    };

    public:
    GameLogic(Model* model);
    void update(float elapsedTime);
    void move_x(int player, int sign, bool retreat);
    void move_z(int player, int sign);
    void attack(int player);
    int nPlayers();

    private:
    void updatePlayer(Player* player, float elapsedTime);
    void updateEnemies(float elapsedTime);
    void spawnEnemy(EnemyType type, float elapsedTime);
    bool isEnemyTooFarAway(Enemy* enemy);
    void maybeSpawnPortal();
    void updateFloorThings(float elapsedTime);
    void killEnemy(Enemy* enemy);
    void killPortal(FloorThing* portal);

    // before abstraction, just implement in place once
    void handlePlayerCollisions(Player* player, float elapsedTime);
};

#endif /* GAMELOGIC_H */
