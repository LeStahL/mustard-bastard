#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

Player::Player(std::string name, int graphicId, WorldPosition position, WorldOrientation orientation) :
        Entity(position), name(name) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}

/*
bool Player::onCollisionWith(Entity* other, void (*callback)(Entity* other)) {
    return false;
}
*/