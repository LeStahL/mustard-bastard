#pragma once

#include <string>

#include <Entity.h>
#include <Weapon.hpp>
#include <GameLogicConst.h>
#include <AttackState.hpp>

enum PlayerState {
    Standing,
    Walking,
    Attacking,
    Warping
};

class Player : public Entity {
private:
    std::string name;

public:
    Weapon *weapon;
    PlayerState state;
    AttackState attack_state;
    float move_z_cooldown = 0.0f;
    float attack_cooldown = 0.0f;
    float power = 1.0f;
    float health = .5f;
    long points = 0;
    float mustardness = 0.;

    const float HALFWIDTH = 80; // <-- put that... elsewhere? it's a bit arbitrary yet.

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
