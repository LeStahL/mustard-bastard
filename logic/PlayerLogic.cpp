#include <PlayerLogic.hpp>

#include <algorithm>
#include <stdexcept>
#include <cmath>

#include <Player.hpp>
#include <GameLogicConst.hpp>
#include <Portal.hpp>
#include <Medikit.hpp>
#include <const.hpp>

void PlayerLogic::beginWarp() {
    player->state = PlayerState::Warping;
    player->lock();
    player->warp_timer = 0;
    player->coords.x_speed = 0;
    player->coords.y = 0;
    warp_did_happen = false;
}

void PlayerLogic::update(float elapsed) {
    player->doCoordUpdates(elapsed);
    player->coords.x = std::clamp(player->coords.x, PLAYER_X_BORDER_MARGIN, WIDTH - PLAYER_X_BORDER_MARGIN);
    player->move_z_cooldown = std::max(player->move_z_cooldown - elapsed, 0.f);
    player->attackCooldown.coolDownBy(elapsed);
    player->attackDuration.coolDownBy(elapsed);

    if (player->state == PlayerState::Attacking && player->attackDuration.cooledDown()) {
        player->state = PlayerState::Standing;
    }

    if (player->state == PlayerState::Warping) {
        player->warp_timer += elapsed;
        if (player->getWarpProgress() >= 0.5 && !warp_did_happen) {
            player->coords.upWorld ^= true;
            warp_did_happen = true;
        }
        if (player->getWarpProgress() >= 1) {
            endWarp();
        }
    }
}

void PlayerLogic::endWarp() {
    player->unlock();
    player->state = PlayerState::Standing;
}

void PlayerLogic::move_x(int sign, bool retreat) {
    if (!player->coords.upWorld) {
        sign *= -1;
    }

    bool would_switch_direction = player->coords.facing_left && (sign > 0)
        || !player->coords.facing_left && (sign < 0);

    if (would_switch_direction && !retreat) {
        player->coords.x_speed = 0;
        player->coords.facing_left ^= true;
    } else if (retreat) {
        player->coords.x_speed = -sign * PLAYER_MOVE_X_SPEED;
    } else {
        player->coords.x_speed = sign * PLAYER_MOVE_X_SPEED;
    }

    if (!player->isLocked()) {
        if (player->coords.x_speed == 0 && player->state == PlayerState::Walking) {
            player->state = PlayerState::Standing;
        }
        else if (player->coords.x_speed != 0 && player->state == PlayerState::Standing) {
            player->state = PlayerState::Walking;
        }
    }
}

void PlayerLogic::move_z(int sign) {
    if (sign == 0)
        return;

    if (player->move_z_cooldown <= 0) {
        player->coords.z = std::clamp(player->coords.z + sign, 0, (int)Z_PLANES - 1);
        player->move_z_cooldown = PLAYER_MOVE_Z_COOLDONW;
    }
}

void PlayerLogic::healUp(float healthPoints) {
    player->health = std::min(player->health + healthPoints, PLAYER_MAX_HEALTH);
}

void PlayerLogic::handleCollisions(Entity *entity, float elapsedTime) {
    if (player->coords.z != entity->coords.z) {
        return;
    }
    auto [playerL, playerR] = player->getCollisionXInterval();
    auto [entityL, entityR] = entity->getCollisionXInterval();
    if (playerL > playerR || entityL > entityR) {
        throw std::runtime_error {"Whatever you did, some entity->getCollisionXInterval() isn't in right order and I DO NOT TOLERATE THAT >:("};
    }
    // special case: check player<->portal collision (could be done better, I know)
    if (Portal* portal = dynamic_cast<Portal*>(entity)) {
        auto playerX = player->coords.x;
        auto portalX = 0.5 * (entityL + entityR);
        if (fabs(playerX - portalX) <= portal->size) {
            beginWarp();
            portal->shutDown();
        }
    } else if(Medikit *medikit = dynamic_cast<Medikit*>(entity)) {
        if(fabs(player->coords.x - medikit->coords.x) <= medikit->width()) {
            healUp(MEDIKIT_HP);
            medikit->wasUsed = true;
        }
    } else if(Weapon *weapon = dynamic_cast<Weapon*>(entity)) {
        if(fabs(player->coords.x - weapon->coords.x) <= weapon->width()*0.5f && player->weapon->type == WeaponType::Hand) {
            delete player->weapon;
            player->weapon = weapon;
            weapon->pickedUp = true;
        }
    } else {
        bool playerCollidesFromLeft = playerL < entityL && playerR >= entityL;
        bool playerCollidesFromRight = playerR > entityR && playerL <= entityR;

        if (playerCollidesFromLeft) {
            player->coords.x += entityL - playerR - 1;
            // TODO: QM: what to do with mass? they should obviously have one.
            player->coords.applyAcceleration(0, 0, true);
            entity->coords.applyAcceleration(0, 0, true);
        } else if (playerCollidesFromRight) {
            player->coords.x += entityR - playerL + 1;
            player->coords.applyAcceleration(0, 0, true);
            entity->coords.applyAcceleration(0, 0, true);
        }
    }
}

// TODO: there's no recoil yet
// also, disallow plane switching if there is a zombie - just make player hurt
// if player hurts, paint him red
