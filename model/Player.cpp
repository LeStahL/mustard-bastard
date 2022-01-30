#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

Player::Player(int graphicId, WorldPosition position, WorldOrientation orientation) :
        IsDrawable(graphicId, DrawType::animation, position, orientation) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}
