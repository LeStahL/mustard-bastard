#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <Model.h>

class GameLogic {
    private:
    Model& model;
    int moveState;

    const double PLAYER_SPEED = 100.0;

    public:
    GameLogic(Model& model);
    void update(float elapsedTime);
    void stay();
    void moveForward();
    void moveBackward();

    private:
    void updatePlayer(float elapsedTime);
};

#endif /* GAMELOGIC_H */