#include <GameViewModel.hpp>

GameViewModel::GameViewModel() {
    zLayer = std::vector<std::vector<IsDrawable*>>(Z_LAYER_COUNT);
}

size_t GameViewModel::getZLayerCount() {
    return Z_LAYER_COUNT;
}

std::vector<IsDrawable*>* GameViewModel::getLayer(int layerIndex) {
    if(layerIndex < Z_LAYER_COUNT)
        return &zLayer[layerIndex];
    
    return nullptr;
}