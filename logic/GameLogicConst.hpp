#pragma once

#include <map>

#include <Interval.hpp>
#include <Entity.hpp>
#include <SimpleEnumsAndStructs.hpp>
#include <Weapon.hpp>

constexpr float PLAYER_MOVE_X_SPEED = 160.0;
constexpr float PLAYER_MOVE_Z_COOLDONW = 0.3;
constexpr float PLAYER_X_BORDER_MARGIN = 30.;
constexpr float PLAYER_MAX_HEALTH = 1.0f;
constexpr float PLAYER_MAX_ACCEPTABLE_MUSTARDNESS = 30;
constexpr float PLAYER_MUSTARDNESS_PER_SPOON = 13;
constexpr float PLAYER_MUSTARDNESS_REDUCTION_FACTOR = 0.5;
constexpr float PLAYER_ATTACK_POWER_REDUCTION_FACTOR = 0.8;
constexpr float PLAYER_ATTACK_POWER_RECREATION = 0.008;
constexpr float PLAYER_ATTACK_POWER_FAIRY_RECREATION = 0.1;
constexpr float PLAYER_MIN_REQUIRED_POWER = 0.3;
constexpr float PLAYER_WARP_TIME = 1.5;
constexpr float PLAYER_ATTACK_DURATION = 0.5f;

constexpr int PORTAL_SPAWN_MODULO = 2000;
constexpr float PORTAL_EPSILON_SIZE = 0.001;
constexpr float PORTAL_GROW_FACTOR = 1.01;
constexpr float PORTAL_WANE_FACTOR = 0.996;
constexpr float PORTAL_ACTIVE_SECONDS = 4;
constexpr float PORTAL_MAX_HALFWIDTH = 42;
constexpr float PORTAL_HEIGHT_RATIO = 0.3;

constexpr int MEDIKIT_SPAWN_MODULO = 2000;
constexpr float MEDIKIT_HP = 0.1f;
constexpr float MEDIKIT_SPAWN_HEIGHT_OFFSET = 30.0f;
constexpr float MEDIKIT_FALL_SPEED_PX_PER_S = -20.0f;
constexpr float MEDIKIT_INITIAL_X_SPEED_PX_PER_S = 50.0f;
constexpr float MEDIKIT_X_FREQUENCY_PER_S = 10.0f;

constexpr float WEAPON_SPAWN_MODULO = 2000;

const std::map<EntityType, Interval> INIT_COOLDOWN = {
    { EntityType::ZombieAndCat, Interval(2, 10)},
    { EntityType::IcebergAndFairy, Interval(120, 210)}
};

const std::map<WeaponType, double> ATTACK_COOLDOWN = {
    { WeaponType::Hand, 500.},
    { WeaponType::Axe, 2000.},
    { WeaponType::Mustard, 1000.},
};

const std::map<EntityType, EnemyStats> INIT_ENEMY_STATS = {
    { EntityType::ZombieAndCat, EnemyStats(30, 3) },
    { EntityType::IcebergAndFairy, EnemyStats(100, 1e6) },
};

const std::map<EntityType, int> FLOOR_THING_SPAWN_MODULO = {
    { EntityType::Portal, PORTAL_SPAWN_MODULO },
    { EntityType::Medikit, MEDIKIT_SPAWN_MODULO},
    { EntityType::Weapon, WEAPON_SPAWN_MODULO}
};
