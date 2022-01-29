#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <GameViewModel.hpp>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        player_moving,
        menu_background,
        game_background
    };

    private:
    GameViewModel gameViewModel;
    Player player;
    std::vector<Entity*> entities;

    public:
    Model();

    GameViewModel& getGameViewModel();

    std::vector<Entity*>& getEntities();
    Player& getPlayer();
};

#endif /* MODEL_H */