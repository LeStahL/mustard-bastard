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

struct EnemyTarget {
    int player_number = -1;
    float fixed_x = -1;
    EnemyTarget(int number, float fixed_x): player_number(number), fixed_x(fixed_x) {}
    EnemyTarget(): player_number(-1), fixed_x(-1) {}
    static EnemyTarget PlayerTarget(int number) { return EnemyTarget(number, -1); }
    static EnemyTarget FixedXTarget(float x) { return EnemyTarget(-1, x); }
    static EnemyTarget NoTarget() { return EnemyTarget(); }
    bool isPlayerTarget() { return player_number > -1; }
};
