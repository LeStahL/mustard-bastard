#include <Enemy.hpp>

Enemy::Enemy(int graphicId, WorldPosition position) :
        Entity(position),
        IsDrawable(graphicId, IsDrawable::DrawType::animation),
        health(100) { // TODO: health festlegen

}