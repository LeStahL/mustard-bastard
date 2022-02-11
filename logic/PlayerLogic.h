#pragma once

#include <Player.h>

class PlayerLogic {
    private:
        Player *player;

    public:
        PlayerLogic(Player *player): player(player) {};

        void move_x(int sign, bool retreat);
        void move_z(int sign);
        void attack();

        void update(float elapsed);
        void beginWarp();
        void endWarp();

        void handleCollisions(Entity *entity, float elapsedTime);

        bool isLocked() {
            return player->isLocked();
        }

        bool canCollide() {
            return player->canCollide();
        }
};
