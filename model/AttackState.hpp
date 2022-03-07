# pragma once

#include <SimpleEnumsAndStructs.h>

class AttackState {
    public:
    float cooldown = 0;
    float mustardedness = 0;

    void setCoolDown(float time) {
        cooldown = time;
    }

    void coolDown(float time) {
        cooldown = cooldown < time ? 0 : cooldown - time;
    }

};
