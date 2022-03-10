#include "Mustard.hpp"
#include "Player.h"

#include <string>

Mustard::Mustard(WorldCoordinates position)
    : Entity(EntityType::IcebergAndFairy, position)
    , Cooldownable(damageWhenConsumedOnCooldown)
    , PlayerAttachable()
{
}

void Mustard::update(float time)
{
    if(PlayerAttachable::isAttachedToPlayer() && isBeingUsed && hasCooldown(time))
    {
        player()->health -= damageWhenConsumedOnCooldown;
    }
    Cooldownable::update(time);
}

float Mustard::damageWhenConsumedOnCooldown = .1;
