#include <Model.hpp>

#include <iostream>

#include <Enemy.hpp>
#include <WorldCoordinates.hpp>

const WorldCoordinates START_PLAYER1 = WorldCoordinates(40., 1, true);
const WorldCoordinates START_PLAYER2 = WorldCoordinates(440., 410, true);

Model::Model()
{
    reset();
}

void Model::reset()
{
    // clear all lists
    for(Player *player : players) {
        delete player;
    }
    players.clear();

    for(Enemy *enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    for(FloorThing *floorThing : floorThings) {
        delete floorThing;
    }
    floorThings.clear();

    // init clean
    gameState = GameState::Running;

    Player* eumel = new Player("Eumel", START_PLAYER1);
    players.push_back(eumel);
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
