#include <AttackLogic.hpp>
#include <GameLogicConst.h>

AttackLogic::AttackLogic(Player *player, std::vector<Enemy *> &enemies) :
    player(player),
    enemies(enemies)
{

}

void AttackLogic::attack()
{
    if(!canAttack())
        return;

    player->state = PlayerState::Attacking;
    player->attackCooldown.setCooldown(player->weapon->coolDown);
    player->attackDuration.setCooldown(PLAYER_ATTACK_DURATION);
    player->power *= PLAYER_ATTACK_POWER_REDUCTION_FACTOR;

    std::vector<Enemy*> enemiesInAttackRange = getEnemiesInAttackRange();

    for(Enemy *enemy : enemiesInAttackRange) {
        enemy->setHealth(enemy->getHealth() - player->weapon->damage);
    }
}

bool AttackLogic::canAttack() const
{
    bool attackCooldownZero = player->attackCooldown.cooledDown();
    bool enoughPower = player->power >= PLAYER_MIN_REQUIRED_POWER;
    bool mustardednessLowEnough = player->mustardness <= PLAYER_MAX_ACCEPTABLE_MUSTARDNESS;

    return attackCooldownZero && enoughPower && mustardednessLowEnough;
}

std::vector<Enemy*> AttackLogic::getEnemiesInAttackRange() const
{
    std::vector<Enemy*> enemiesInAttackRange;

    for(Enemy *enemy : enemies) {
        enemiesInAttackRange.push_back(enemy);
    }

    return enemiesInAttackRange;
}
