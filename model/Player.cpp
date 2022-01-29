#include <Player.h>
#include <WorldPosition.h>

Player::Player() :
        IsDrawable(0, DrawType::animation),
        Entity(WorldPosition(0.0, 0, true)) {

}

Player::Player(int graphicId, WorldPosition position) :
        IsDrawable(graphicId, DrawType::animation),
        Entity(position) {

}

Player::Player(int graphicId, WorldPosition position, WorldOrientation orientation) :
        IsDrawable(graphicId, DrawType::animation),
        Entity(position, orientation) {

}