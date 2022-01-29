#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <IsDrawable.hpp>

class Player : public Entity, public IsDrawable{
    private:
    AttackState attack_state;

    public:
    Player();
    Player(int graphicId, WorldPosition position);
    Player(int graphicId, WorldPosition position, WorldOrientation orientation);

};

#endif /* PLAYER_H */