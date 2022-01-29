#include <Enemy.hpp>

Enemy::Enemy(int graphicId, WorldPosition position) :
        Entity(position),
        IsDrawable(graphicId, IsDrawable::DrawType::animation),
        health(100),
        speed(500) { // TODO: health festlegen

}