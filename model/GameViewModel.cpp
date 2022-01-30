#include <GameViewModel.hpp>

GameViewModel::GameViewModel(ViewStuff *viewStuff, Model *model) :
        viewStuff(viewStuff), model(model)
    {
    zLayer = std::vector<std::vector<IsDrawable*>>(Z_LAYER_COUNT);

    // gameViewModel.getLayer(0)->push_back(&background);

    getLayer(0)->push_back(viewStuff);

    // add player 1
    for (int p = 0; p < model->getNumberOfPlayers(); p++)
    {
        getLayer(1)->push_back(model->getPlayer(p));
    }
}

size_t GameViewModel::getZLayerCount() {
    return Z_LAYER_COUNT;
}

std::vector<IsDrawable*>* GameViewModel::getLayer(int layerIndex) {
    if(layerIndex < Z_LAYER_COUNT)
        return &zLayer[layerIndex];

    return nullptr;
}

void GameViewModel::syncDrawableEntities()
{
    // kind of a hack: sync IsDrawables with Entities for relevant actors
    for (int p = 0; p < model->getNumberOfPlayers(); p++)
    {
        auto player = model->getPlayer(p);
        player->x = player->position.x;
        player->y = viewStuff->getBackgroundBaseLine(player->position);
        player->facing_left = player->orientation.facing_left;
    }

    for (FloorThing* floory : model->getFloorThings())
    {
        floory->x = floory->position.x;
        floory->y = viewStuff->getBackgroundBaseLine(floory->position);
    }
}

void GameViewModel::removeById(int id)
{
    for(int i = 0; i < Z_LAYER_COUNT; i++) {
        auto layer = *getLayer(i);
        for(auto it = layer.begin(); it != layer.end(); it++) {
            if((*it)->id == id) {
                layer.erase(it);
                return;
            }
        }
    }
}