#include "Enemy.hpp"
#include <Model.h>

#include <WorldCoordinates.h>
#include <iostream>

const WorldCoordinates START_PLAYER1 = WorldCoordinates(40., 1, true);
const WorldCoordinates START_PLAYER2 = WorldCoordinates(440., 410, true);

Model::Model()
{
    // ignore background for now
    // background = Object(GraphicsId::game_background, IsDrawable::DrawType::texture, WorldCoordinates(0, 0, true));
    Player* eumel = new Player("Eumel", START_PLAYER1);
    players.push_back(eumel);
    //players.push_back(new Player(GraphicsId::player_standing, START_PLAYER2));
    //players.at(1)->name = "Bert";

    gameState = GameState::Running;
}

void Model::setGameState(const GameState newGameState)
{
    gameState = newGameState;
}

Model::GameState Model::getGameState() const
{
    return gameState;
}

Player* Model::getPlayer(int player_number) {
    try {
        return players.at(player_number);
    }
    catch (const std::out_of_range& err) {
        return nullptr;
    }
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
