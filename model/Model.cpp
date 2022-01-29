#include <Model.h>

#include <WorldPosition.h>
#include <Player.h>


Model::Model() {
    entities.push_back(Player(WorldPosition(5.0, 1, true)));
    entities.push_back(Player(WorldPosition(5.0, 1, true)));
}

std::vector<Entity>& Model::getEntities() {
    return entities;
}