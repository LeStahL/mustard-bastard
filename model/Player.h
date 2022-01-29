#ifndef PLAYER_H
#define PLAYER_H

#include <IsDrawable.hpp>

class Player :  public IsDrawable{
    public:
    Player(int graphicId, WorldPosition position);
};

#endif /* PLAYER_H */