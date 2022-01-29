#pragma once

#include <vector>
#include <IsDrawable.hpp>
#include <ViewStuff.h>
#include <Model.h>

constexpr size_t Z_LAYER_COUNT = 3;

class GameViewModel {
    private:
    std::vector<std::vector<IsDrawable*>> zLayer;
    ViewStuff* viewStuff;
    Model* model;

    public:
    GameViewModel(ViewStuff *viewStuff, Model *model);

    size_t getZLayerCount();
    std::vector<IsDrawable*>* getLayer(int layerIndex);
    void syncDrawableEntities();
};