#include "Entity.h"
#include <Enemy.hpp>
#include <helpers.h>

Enemy* Enemy::getZombie(WorldCoordinates position) {
    return new Enemy(EntityType::ZombieAndCat, position);
}

Enemy* Enemy::getIceberg(WorldCoordinates position) {
    return new Enemy(EntityType::IcebergAndFairy, position);
}

void Enemy::target(int player_number) {
    state = EnemyState::Targeting;
    targetPlayer = player_number;
}

void Enemy::target(float x) {
    state = EnemyState::Targeting;
    targetX = x;
}

void Enemy::lose_target() {
    state = EnemyState::Idle;
}

auto needsTurnAround = [](Enemy self, float target_x) {
    if (sgn(self.speed) != sgn(target_x - self.coords.x)) {
        self.speed = 0;
        self.coords.facing_left ^= true;
    }
};
