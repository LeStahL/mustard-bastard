#pragma once

#include <Player.hpp>

class PlayerLogic {
private:
    Player *player;

    bool warp_did_happen;

public:
    PlayerLogic(Player *player): player(player) {};

    void move_x(int sign, bool retreat);
    void move_z(int sign);

    void update(float elapsed);
    void beginWarp();
    void endWarp();

    void healUp(float healthPoints);
    void pickUpWeapon(Weapon *weapon);

    void handleCollisions(Entity *entity, float elapsedTime);

    bool isLocked() {
        return player->isLocked();
    }

    bool canCollide() {
        return player->canCollide();
    }
};
