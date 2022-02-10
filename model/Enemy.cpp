#include "Entity.h"
#include <Enemy.hpp>

Enemy* Enemy::getZombie(WorldPosition position) {
    return new Enemy(EntityType::ZombieAndCat, position);
}

Enemy* Enemy::getIceberg(WorldPosition position) {
    return new Enemy(EntityType::IcebergAndFairy, position);
}