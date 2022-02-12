#include <Player.h>
#include <WorldCoordinates.h>

Player::Player(std::string name, WorldCoordinates coords) :
        Entity(EntityType::Player, coords), name(name) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}

std::pair<float, float> Player::getCollisionXInterval() {
    return std::pair(coords.x - HALFWIDTH, coords.x + HALFWIDTH);
}

bool Player::canCollide() {
    return state != PlayerState::Warping;
}

bool Player::isLocked() {
    return is_locked;
}

/*
bool Player::onCollisionWith(Entity* other, void (*callback)(Entity* other)) {
    return false;
}
*/