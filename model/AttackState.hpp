#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

enum Weapon {
    Hand,
    Axe,
    Mustard
};

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

#endif ATTACKSTATE_H