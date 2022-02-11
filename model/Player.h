#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <AttackState.hpp>
#include <GameLogicConst.h>
#include <string>

enum PlayerState {
    Standing,
    Walking,
    Attacking,
    Warping
};

class Player : public Entity {
    std::string name;

    public:
    Weapon *weapon;
    PlayerState state;
    float move_z_cooldown = 0.0f;
    AttackState attack_state;
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

#endif /* PLAYER_H */
