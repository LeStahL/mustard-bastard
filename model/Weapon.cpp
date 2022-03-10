#include <Weapon.hpp>
#include <ViewConst.hpp>

Weapon::Weapon(
        WeaponType type,
        int damage, float attackRange,
        float coolDown,
        WorldCoordinates position) :
    FloorThing(EntityType::Weapon, position),
    type(type),
    damage(damage),
    attackRange(attackRange),
    coolDown(coolDown),
    pickedUp(false)
{

}

Weapon *Weapon::getHand()
{
    return new Weapon(
                WeaponType::Hand,
                WEAPON_HAND_DAMAGE,
                WEAPON_HAND_ATTACKRANGE,
                WEAPON_HAND_COOLDOWN,
                WorldCoordinates(0.0f, 0.0f, false));
}

Weapon *Weapon::getAxe(WorldCoordinates position)
{
    return new Weapon(
                WeaponType::Axe,
                WEAPON_AXE_DAMAGE,
                WEAPON_AXE_ATTACKRANGE,
                WEAPON_AXE_COOLDOWN,
                position);
}

float Weapon::width() const
{
    return static_cast<float>(AXE_PIXEL_WIDTH);
}
