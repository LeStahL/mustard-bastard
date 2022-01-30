#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Enemy.hpp>
#include <FloorThing.hpp>
#include <Object.h>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        zombie,
        iceberg,
        cat,
        game_background
    };

    private:
    std::vector<Player*> players;
    // Object background;
    std::vector<Enemy*> enemies;
    std::vector<Entity*> entities;
    std::vector<FloorThing*> floorThings;

    public:
    Model();

    std::vector<Entity*>& getEntities();
    Player* getPlayer(int player_number);
    int getNumberOfPlayers();
    std::vector<Enemy*>& getEnemies();
    std::vector<FloorThing*>& getFloorThings();
};

#endif /* MODEL_H */