#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <AttackState.hpp>

enum PlayerState {
    Standing,
    Walking,
    Attacking
};

class Player : public Entity {
    public:
    PlayerState state;
    float move_z_cooldown;
    AttackState attack_state;
    float power = 1;
    long points = 0;

    Player(int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(int graphicId, WorldPosition position) : Player(graphicId, position, WorldOrientation())
    {}

};

#endif /* PLAYER_H */