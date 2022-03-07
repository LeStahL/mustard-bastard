# pragma once

#include <SimpleEnumsAndStructs.h>
#include <WorldCoordinates.h>
#include <Weapon.hpp>

class AttackState {
    public:
    Weapon weapon;
    float cooldown = 0;
    float mustardedness = 0;

    AttackState(): weapon(WeaponType::Hand, WorldCoordinates(0.0f, 0.0f, true))
    { }

    void setCoolDown(float time) {
        cooldown = time;
    }

    void coolDown(float time) {
        cooldown = cooldown < time ? 0 : cooldown - time;
    }

};
