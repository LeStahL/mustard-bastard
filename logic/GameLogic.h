#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <Model.h>

class GameLogic {
    private:
    Model& model;

    const double PLAYER_SPEED = 160.0;

    public:
    GameLogic(Model& model);
    void update(float elapsedTime);
    void move_x(int player, int sign);
    int nPlayers();

    private:
    void updatePlayer(Player* player, float elapsedTime);
};

#endif /* GAMELOGIC_H */
