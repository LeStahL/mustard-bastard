#pragma once

#include <string>

#include <Entity.hpp>
#include <WorldCoordinates.hpp>
#include <Weapon.hpp>
#include <GameLogicConst.hpp>
#include <Cooldown.hpp>
#include <ViewConst.hpp>

enum class PlayerState {
    Standing,
    Walking,
    Attacking,
    Warping
};

class Player : public Entity {
private:
    std::string name;

public:
    PlayerState state;
    Weapon *weapon;   
    float move_z_cooldown = 0.0f;
    Cooldown attackCooldown;
    Cooldown attackDuration;

    float power = 1.0f;
    float health = .5f;
    long points = 0;
    float mustardness = 0.;

    const float HALFWIDTH = BASTARD_STANDING_PIXEL_WIDTH*0.5f; // <-- put that... elsewhere? it's a bit arbitrary yet.

    float warp_timer; // --> gonna be a Cooldownable / Timerthingy / whatever

    Player(std::string name, WorldCoordinates coords);

    std::pair<float, float> getCollisionXInterval() override;
    bool canCollide() override;
    bool isLocked();

    float getWarpProgress() { return warp_timer / PLAYER_WARP_TIME; }

    void lock() { is_locked = true; }
    void unlock() { is_locked = false; }

    std::string getName();

};
