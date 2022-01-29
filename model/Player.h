#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <IsDrawable.hpp>

class Player : public Entity, public IsDrawable{
    public:
    Player();
    Player(int graphicId, WorldPosition position);

    
};

#endif /* PLAYER_H */