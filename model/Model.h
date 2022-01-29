#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <GameViewModel.hpp>

class Model {
    public:
    enum GraphicsId {
        menu_background,
        game_background,
        player_standing,
        player_moving
    };

    private:
    GameViewModel gameViewModel;
    Player player;
    std::vector<Entity*> entities;

    public:
    Model();
    std::vector<Entity*>& getEntities();
    Player& getPlayer();
};

#endif /* MODEL_H */