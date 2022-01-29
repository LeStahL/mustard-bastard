#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>


Model::Model() :
        player(Player(GraphicsId::player_standing, WorldPosition(6.0, 1, true))) {

    // add player drawing to layer 1
    gameViewModel.getLayer(1)->push_back(&player);
}

std::vector<Entity*>& Model::getEntities() {
    return entities;
}

Player& Model::getPlayer() {
    return player;
}
