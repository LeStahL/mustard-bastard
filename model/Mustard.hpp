#pragma once

#include "Entity.h"
#include "Cooldownable.hpp"
#include "PlayerAttachable.hpp"

class Mustard : public Entity, public PlayerAttachable, public Cooldownable {
    public:
    Mustard(WorldCoordinates position);
    ~Mustard();

    static float damageWhenConsumedOnCooldown;
    void update(float time);
};
