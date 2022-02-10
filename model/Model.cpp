#include "Enemy.hpp"
#include <Model.h>

#include <WorldPosition.h>
#include <iostream>

const WorldPosition START_PLAYER1 = WorldPosition(40., 1, true);
const WorldPosition START_PLAYER2 = WorldPosition(440., 410, true);

Model::Model()
{
    // ignore background for now
    // background = Object(GraphicsId::game_background, IsDrawable::DrawType::texture, WorldPosition(0, 0, true));
    Player* eumel = new Player(START_PLAYER1);
    players.push_back(eumel);
    //players.push_back(new Player(GraphicsId::player_standing, START_PLAYER2));
    //players.at(1)->name = "Bert";
}

Player* Model::getPlayer(int player_number) {
    return players[player_number];
}

int Model::getNumberOfPlayers() {
    return players.size();
}

std::vector<Enemy*>& Model::getEnemies() {
    return enemies;
}

std::vector<FloorThing*>& Model::getFloorThings() {
    return floorThings;
}