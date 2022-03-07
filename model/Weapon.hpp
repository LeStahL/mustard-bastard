#pragma once

#include <FloorThing.hpp>
#include <WorldCoordinates.h>

constexpr int   WEAPON_HAND_DAMAGE = 5;
constexpr float WEAPON_HAND_ATTACKRANGE = 30.0f;
constexpr float WEAPON_HAND_COOLDOWN = 5.0f;
constexpr int   WEAPON_AXE_DAMAGE = 20;
constexpr float WEAPON_AXE_ATTACKRANGE = 15.0f;
constexpr float WEAPON_AXE_COOLDOWN = 10.0f;

enum class WeaponType {
    Hand,
    Axe,
    Mustard
};

class Weapon : public FloorThing {
public:
    const WeaponType type;
    const int damage;
    const float attackRange;
    const float coolDown;

private:
    Weapon(WeaponType type,
           int damage,
           float attackRange,
           float coolDown,
           WorldCoordinates position);

public:
    static Weapon *getHand();
    static Weapon *getAxe(WorldCoordinates position);
};
