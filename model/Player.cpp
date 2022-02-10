#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

Player::Player(WorldPosition position, WorldOrientation orientation) :
        Entity(EntityType::Player, position) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}

/*
bool Player::onCollisionWith(Entity* other, void (*callback)(Entity* other)) {
    return false;
}
*/