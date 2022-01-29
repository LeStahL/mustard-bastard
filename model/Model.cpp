#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>
#include <Object.h>

const WorldPosition START_PLAYER1 = WorldPosition(20., 1, true);

Model::Model(ViewStuff* viewStuff) :
		viewStuff(viewStuff)
{
    // ignore background for now
    // background = Object(GraphicsId::game_background, IsDrawable::DrawType::texture, WorldPosition(0, 0, true));
    // gameViewModel.getLayer(0)->push_back(&background);

    gameViewModel.getLayer(0)->push_back(viewStuff);

    // add player 1
    players.push_back(new Player(GraphicsId::player_standing, START_PLAYER1));
    // add player 1 drawing to layer 1
    gameViewModel.getLayer(1)->push_back(players[0]);
}

GameViewModel& Model::getGameViewModel() {
    return gameViewModel;
}

std::vector<Entity*>& Model::getEntities() {
    return entities;
}

Player* Model::getPlayer(int player_number) {
    return players[player_number];
}

int Model::getNumberOfPlayers() {
    return players.size();
}