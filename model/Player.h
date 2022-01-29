#ifndef PLAYER_H
#define PLAYER_H

#include <IsDrawable.hpp>

class Player : public IsDrawable{
    private:
    AttackState attack_state;

    public:
    Player(int graphicId, WorldPosition position, WorldOrientation orientation);

};

#endif /* PLAYER_H */