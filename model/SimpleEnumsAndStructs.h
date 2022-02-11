#pragma once

enum class EnemyState {
    Idle,
    Targeting,
    Attacking,
    Dying,
};

struct EnemyStats {
    float health, armor;
    EnemyStats(float health, float armor): health(health), armor(armor) {}
    EnemyStats(): EnemyStats(1, 0) {}
};

enum Weapon {
    Hand,
    Axe,
    Mustard
};