#include "Weapon.hpp"

Weapon::Weapon(WeaponType type,WorldCoordinates position)
    : Entity(EntityType::ZombieAndCat, position)
    , Cooldownable(cooldowns[type])
    , PlayerAttachable()
{

}

void Weapon::update(float time)
{
    Cooldownable::update(time);
}

std::map<WeaponType, float> Weapon::cooldowns = {
    {WeaponType::Hand, 1},
    {WeaponType::Axe, 2}
};
