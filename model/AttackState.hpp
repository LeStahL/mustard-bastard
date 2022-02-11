# pragma once

#include <SimpleEnumsAndStructs.h>

class AttackState {
    public:
    Weapon weapon;
    float cooldown = 0;
    float mustardedness = 0;

    AttackState(): weapon(Weapon::Hand)
    { }

    void setCoolDown(float time) {
        cooldown = time;
    }

    void coolDown(float time) {
        cooldown = cooldown < time ? 0 : cooldown - time;
    }

};