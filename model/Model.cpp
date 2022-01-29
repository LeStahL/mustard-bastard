#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>
#include <Object.h>

Model::Model() :
        player(Player(GraphicsId::player_standing, WorldPosition(6.0, 1, true))),
        background(Object(GraphicsId::game_background, IsDrawable::DrawType::texture, WorldPosition(0, 0, true))) {

    // add player drawing to layer 1
    gameViewModel.getLayer(0)->push_back(&background);
    gameViewModel.getLayer(1)->push_back(&player);
    
}

GameViewModel& Model::getGameViewModel() {
    return gameViewModel;
}

std::vector<Entity*>& Model::getEntities() {
    return entities;
}

Player& Model::getPlayer() {
    return player;
}
