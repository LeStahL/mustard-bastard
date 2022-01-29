#ifndef ATTACKSTATE_H
#define ATTACKSTATE_H

enum Weapon {
    Hand,
    Axe,
    Mustard
};

class AttackState {
    private:
    float cooldown = 0;

    public:
    Weapon weapon;

    AttackState(): weapon(Weapon::Hand) {

    }

    void setCoolDown(float time) {
        cooldown = time;
    }

    void coolDown(float time) {
        cooldown = cooldown < time ? 0 : cooldown - time;
    }

    bool isCool() {
        return cooldown <= 0;
    }


};

#endif ATTACKSTATE_H