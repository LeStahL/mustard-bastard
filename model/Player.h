#ifndef PLAYER_H
#define PLAYER_H

#include <IsDrawable.hpp>
#include <AttackState.hpp>

enum PlayerState {
    Standing,
    Walking,
    Attacking
};

class Player : public IsDrawable {
    public:
    PlayerState state;
    float move_z_cooldown;
    AttackState attack_state;
    float power = 1;
    float health = 100;
    long points = 0;

    Player(int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(int graphicId, WorldPosition position) : Player(graphicId, position, WorldOrientation())
    {}

};

#endif /* PLAYER_H */