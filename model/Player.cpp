#include <Player.h>
#include <WorldPosition.h>

Player::Player(int graphicId, WorldPosition position) :
        IsDrawable(graphicId, DrawType::animation, position) {

}