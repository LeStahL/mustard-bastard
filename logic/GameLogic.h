#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <map>
#include <Model.h>
#include <AttackState.hpp>
#include <FloorThing.hpp>

class GameLogic {
    private:
    Model* model;

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
    void maybeSpawnEnemy(EnemyType type);
    bool isEnemyTooFarAway(Enemy* enemy);
    void maybeSpawnPortal();
    void updateFloorThings(float elapsedTime);
    void killEnemy(Enemy* enemy);
    void killPortal(FloorThing* portal);
};

#endif /* GAMELOGIC_H */
