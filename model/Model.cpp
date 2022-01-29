#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>


Model::Model() :
        player(Player(WorldPosition(6.0, 1, true))) {
    entities.push_back(new Player(WorldPosition(5.0, 1, true)));
    entities.push_back(new Player(WorldPosition(5.0, 1, true)));
}

std::vector<Entity*>& Model::getEntities() {
    return entities;
}

Player& Model::getPlayer() {
    return player;
}
