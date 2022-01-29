#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Object.h>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        game_background,
        player_moving,
        menu_background
    };

    private:
    std::vector<Player*> players;
    // Object background;
    std::vector<Entity*> entities;

    public:
    Model();

    std::vector<Entity*>& getEntities();
    Player* getPlayer(int player_number);
    int getNumberOfPlayers();
};

#endif /* MODEL_H */