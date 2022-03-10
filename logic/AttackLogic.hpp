#pragma once

#include <vector>

#include <Player.h>
#include <Enemy.hpp>

class AttackLogic {
private:
    Player *player;
    std::vector<Enemy*> &enemies;

public:
    AttackLogic(Player *player, std::vector<Enemy*> &enemies);
    void attack();

private:
    bool canAttack() const;
    std::vector<Enemy*> getEnemiesInAttackRange() const;
};
