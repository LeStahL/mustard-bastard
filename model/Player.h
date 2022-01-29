#ifndef PLAYER_H
#define PLAYER_H

#include <IsDrawable.hpp>
#include <AttackState.hpp>

class Player : public IsDrawable {
    private:
    AttackState attack_state;

    public:
    Player(int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(int graphicId, WorldPosition position) : Player(graphicId, position, WorldOrientation())
    {}


};

#endif /* PLAYER_H */