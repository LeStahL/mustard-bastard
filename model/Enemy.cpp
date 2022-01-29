#include <Enemy.hpp>

Enemy::Enemy(int graphicId, EnemyType type, WorldPosition position) :
        IsDrawable(graphicId, IsDrawable::DrawType::animation, position),
        type(type) {
}