#include <Enemy.hpp>

Enemy::Enemy(EnemyType type, WorldPosition position) :
        Entity(position),
        type(type) {
}