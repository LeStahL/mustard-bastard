#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

// wegen update() haben wir jetzt hier Logik-Abhängigkeiten. Ist halt erstmal so.
#include <GameLogic.h>
#include <GameLogicConst.h>
#include <const.h>
#include <algorithm>

Player::Player(std::string name, int graphicId, WorldPosition position, WorldOrientation orientation) :
        Entity(position), name(name) {
    state = PlayerState::Standing;
    attack_state = AttackState();
}

std::pair<float, float> Player::getCollisionXInterval() {
    return std::pair(position.x - HALFWIDTH, position.x + HALFWIDTH);
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