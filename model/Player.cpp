#include <Player.h>
#include <WorldCoordinates.h>
#include "Weapon.hpp"

Player::Player(std::string name, WorldCoordinates coords) :
    Entity(EntityType::Player, coords),
    name(name),
    weapon(new Weapon(WeaponType::Hand, WorldCoordinates(0.0, 0.0, false))),
    warp_timer(0.0f)
{

}

std::string Player::getName()
{
    return name;
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
