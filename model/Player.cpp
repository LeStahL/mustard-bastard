#include <Player.h>
#include <WorldPosition.h>

Player::Player() :
        IsDrawable(0, DrawType::animation),
        Entity(WorldPosition(0.0, 0, true)) {
        
}

Player::Player(int graphicType, WorldPosition position) :
        IsDrawable(graphicId, DrawType::animation),
        Entity(position) {

}