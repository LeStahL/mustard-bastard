#include <Player.h>
#include <WorldPosition.h>
#include <WorldOrientation.h>

// wegen update() haben wir jetzt hier Logik-Abhängigkeiten. Ist halt erstmal so.
#include <GameLogic.h>
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

bool Player::isCollisionActive() {
    return state != PlayerState::Warping;
}

/*
bool Player::onCollisionWith(Entity* other, void (*callback)(Entity* other)) {
    return false;
}
*/

void Player::beginWarp() {
    state = PlayerState::Warping;
    warp_timer = 0;
}

// moved here from GameLogic::updatePlayer.
// could also be a PlayerController or whatevs that accesses the Player from outside.
// but it's not. for now.
void Player::update(float elapsed) {
    position.x = std::clamp(
        position.x + x_speed * elapsed,
        PLAYER_X_BORDER_MARGIN,
        WIDTH - PLAYER_X_BORDER_MARGIN
    );
    move_z_cooldown = std::max(move_z_cooldown - elapsed, 0.f);
    attack_state.coolDown(elapsed);

    if (state == PlayerState::Warping) {
        warp_timer += elapsed;
        if (warp_timer > WARP_TIME) {
            endWarp();
        }
    }
}

void Player::endWarp() {
    state = PlayerState::Standing;
}