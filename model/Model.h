#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>
#include <Object.h>
#include <GameViewModel.hpp>
#include <ViewStuff.h>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        game_background,
        player_moving,
        menu_background
    };

    private:
    GameViewModel gameViewModel; // see below, one could move gameViewModel out of Model, together with viewStuff
    std::vector<Player*> players;
    // Object background;
    std::vector<Entity*> entities;

    public:
    Model(ViewStuff* viewStuff);
    GameViewModel& getGameViewModel();

    ViewStuff* viewStuff; // should not be here, but it is! lel! move whenever you feel like it.
    std::vector<Entity*>& getEntities();
    Player* getPlayer(int player_number);
    int getNumberOfPlayers();
};

#endif /* MODEL_H */