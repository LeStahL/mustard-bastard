#pragma once

#include "Entity.h"
#include "PlayerAttachable.hpp"
#include "Cooldownable.hpp"

#include <string>
#include <map>

enum WeaponType {
    Hand,
    Axe
};

class Weapon : public Entity, public Cooldownable, public PlayerAttachable {
    private:
    static std::map<WeaponType, float> cooldowns;

    public:
    Weapon(WeaponType type, WorldCoordinates position);
    ~Weapon();

    WeaponType type;
    int damageOnHit;
    void update(float time);
};
