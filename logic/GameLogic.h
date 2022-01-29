#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <model/Model.h>

class GameLogic {
    private:
    Model& model;
    int moveState;

    const double PLAYER_SPEED = 0.5;

    public:
    GameLogic(Model& model);
    void update(int elapsedTime);
    void moveForward();
    void moveBackward();

    private:
    void updatePlayer(int elapsedTime);
}

#endif /* GAMELOGIC_H */