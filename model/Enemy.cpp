#include <Enemy.hpp>

Enemy::Enemy(int graphicId, WorldPosition position) :
        IsDrawable(graphicId, IsDrawable::DrawType::animation, position),
        health(100),
        speed(500) { // TODO: health festlegen

}