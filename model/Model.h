#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Enemy.hpp>
#include <Object.h>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        player_walking,
        player_attack,
        zombie,
        cat,
        iceberg,
        fairy
    };

    private:
    std::vector<Player*> players;
    // Object background;
    std::vector<Enemy*> enemies;
    std::vector<Entity*> entities;

    public:
    Model();

    std::vector<Entity*>& getEntities();
    Player* getPlayer(int player_number);
    int getNumberOfPlayers();
    std::vector<Enemy*>& getEnemies();
};

#endif /* MODEL_H */