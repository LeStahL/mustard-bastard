#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Enemy.hpp>
#include <Object.h>
#include <GameViewModel.hpp>
#include <ViewStuff.h>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        zombie,
        game_background
    };

    private:
    GameViewModel gameViewModel;
    ViewStuff* viewStuff;
    Player player;
    Object background;
    std::vector<Enemy*> enemies;
    std::vector<Entity*> entities;

    public:
    Model(ViewStuff* viewStuff);

    GameViewModel& getGameViewModel();

    std::vector<Entity*>& getEntities();
    std::vector<Enemy*>& getEnemies();
    Player& getPlayer();
};

#endif /* MODEL_H */