#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <AttackState.hpp>

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

    Player(std::string name, int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(std::string name, int graphicId, WorldPosition position) : Player(name, graphicId, position, WorldOrientation())
    {}

//    bool onCollisionWith(Entity* other, void (*callback)(Entity* other)) override;
};

#endif /* PLAYER_H */