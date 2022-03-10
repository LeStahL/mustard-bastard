#include <Enemy.hpp>

#include <Entity.hpp>
#include <helpers.hpp>
#include <Model.hpp>
#include <ViewConst.hpp>

Enemy::Enemy(EntityType type, WorldCoordinates coords) :
    Entity(type, coords),
    health(10.0f)
{
    //stats = INIT_ENEMY_STATS.at(type);
}

Enemy* Enemy::getZombie(WorldCoordinates position) {
    return new Enemy(EntityType::ZombieAndCat, position);
}

Enemy* Enemy::getIceberg(WorldCoordinates position) {
    return new Enemy(EntityType::IcebergAndFairy, position);
}

void Enemy::targetPlayer(int player_number) {
    state = EnemyState::Targeting;
    target = EnemyTarget::PlayerTarget(player_number);
}

void Enemy::targetFixedX(float x) {
    state = EnemyState::Targeting;
    target = EnemyTarget::FixedXTarget(x);
}

void Enemy::lose_target() {
    state = EnemyState::Idle;
    target = EnemyTarget::NoTarget();
}

const float TIME_AFTER_WHICH_MISSING_TARGET_IS_LOST = 5;
const float ACCELERATION_TOWARDS_FIXED_X = 45;

void Enemy::doTargetUpdates(Model* model, float deltaT) {
    if (state != EnemyState::Targeting)
        return;

    // currently, there are two options: the enemy is targeting a certain player...
    if (target.isPlayerTarget()) {
        auto playerTarget = model->getPlayer(target.player_number);

        if (playerTarget->coords.z != deltaT) {
            missing_target_player_for_seconds += deltaT;
        }
        if (missing_target_player_for_seconds > TIME_AFTER_WHICH_MISSING_TARGET_IS_LOST) {
            lose_target();
        }

    // ... or a fixed X coordinate.
    } else {
        coords.x_acc = sgn(target.fixed_x) * ACCELERATION_TOWARDS_FIXED_X;
    }
}

std::pair<float, float> Enemy::getCollisionXInterval()
{
    switch (type) {
        case EntityType::ZombieAndCat:
            return std::pair<float, float>(coords.x-ZOMBIE_PIXEL_WIDTH*0.5f, coords.x+ZOMBIE_PIXEL_WIDTH*0.5f);
        default:
            return Entity::getCollisionXInterval();
    }
}
