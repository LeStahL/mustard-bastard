#pragma once

#include <vector>
#include <IsDrawable.hpp>

constexpr size_t Z_LAYER_COUNT = 3;

class GameViewModel {
    private:
    std::vector<std::vector<IsDrawable*>> zLayer;

    public:
    GameViewModel();

    size_t getZLayerCount();
    std::vector<IsDrawable*>* getLayer(int layerIndex);
};