#pragma once

#include "Entity.h"
#include "PlayerAttachable.hpp"
#include "Cooldownable.hpp"

#include <string>
#include <map>

enum class WeaponType {
    Hand,
    Axe,
    Mustard
};

class Weapon : public Entity, public Cooldownable, public PlayerAttachable {
    private:
    static std::map<WeaponType, float> cooldowns;

    public:
    Weapon(WeaponType type, WorldCoordinates position);

    WeaponType type;
    int damageOnHit;
    float attackRange;
    void update(float time);
};
