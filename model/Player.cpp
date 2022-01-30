#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

Player::Player(int graphicId, WorldPosition position, WorldOrientation orientation) :
        Entity(position) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}
