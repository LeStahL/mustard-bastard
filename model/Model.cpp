#include <Model.h>

#include <WorldPosition.h>
#include <iostream>

const WorldPosition START_PLAYER1 = WorldPosition(40., 1, true);

Model::Model() {
    players.push_back(Player(GraphicsId::player_standing, START_PLAYER1));
    //enemies.push_back(Enemy(EnemyType::IcebergAndFairy, WorldPosition(500.0f, 1, true)));
    //enemies.push_back(Enemy(EnemyType::ZombieAndCat, WorldPosition(20.0f, 0, true)));  
}
Player* Model::getPlayer(int player_number) {
    return &players[player_number];
}

int Model::getNumberOfPlayers() {
    return players.size();
}

std::vector<Enemy>& Model::getEnemies() {
    return enemies;
}

std::vector<FloorThing>& Model::getFloorThings() {
    return floorThings;
}