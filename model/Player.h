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
    public:
    PlayerState state;
    float move_z_cooldown;
    AttackState attack_state;
    float power = 1;
    float health = .5;
    long points = 0;
    std::string name;

    const float HALFWIDTH = 50;

    float warp_timer; // --> gonna be a Cooldownable / Timerthingy / whatever

    public:
    Player(std::string name, int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(std::string name, int graphicId, WorldPosition position) : Player(name, graphicId, position, WorldOrientation())
    {}

    std::pair<float, float> getCollisionXInterval() override;
    bool canCollide() override;
    bool isLocked();

    float getWarpProgress() { return warp_timer / PLAYER_WARP_TIME; }

    void lock() { is_locked = true; }
    void unlock() { is_locked = false; }
};

#endif /* PLAYER_H */