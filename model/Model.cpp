#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>
#include <Object.h>

const WorldPosition START_PLAYER1 = WorldPosition(20., 1, true);

Model::Model()
{
    // ignore background for now
    // background = Object(GraphicsId::game_background, IsDrawable::DrawType::texture, WorldPosition(0, 0, true));

    players.push_back(new Player(GraphicsId::player_standing, START_PLAYER1));
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