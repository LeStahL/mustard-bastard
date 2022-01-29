#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Object.h>
#include <GameViewModel.hpp>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        game_background,
        player_moving,
        menu_background
    };

    private:
    GameViewModel gameViewModel;
    Player player;
    Object background;
    std::vector<Entity*> entities;

    public:
    Model();

    GameViewModel& getGameViewModel();

    std::vector<Entity*>& getEntities();
    Player& getPlayer();
};

#endif /* MODEL_H */