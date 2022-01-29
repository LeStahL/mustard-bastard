#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <map>
#include <Model.h>
#include <GameViewModel.hpp>
#include <AttackState.hpp>

class GameLogic {
    private:
    Model* model;
    GameViewModel* gameViewModel;

    const double PLAYER_SPEED = 160.0;
    const std::map<Weapon, double> ATTACK_COOLDOWN = {
        {Weapon::Hand, 500.},
        {Weapon::Axe, 2000.},
        {Weapon::Mustard, 1000.},
    };

    public:
    GameLogic(Model* model, GameViewModel* gameViewModel);
    void update(float elapsedTime);
    void move_x(int player, int sign, bool retreat);
    void move_z(int player, int sign);
    void attack(int player);
    int nPlayers();

    private:
    void updatePlayer(Player* player, float elapsedTime);
    void updateEnemies(float elapsedTime);
    void spawnEnemy();
    bool isEnemyToFarAway(Enemy* enemy);
    void killEnemy(Enemy* enemy);
};

#endif /* GAMELOGIC_H */

