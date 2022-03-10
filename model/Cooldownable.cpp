#include "Cooldownable.hpp"

Cooldownable::Cooldownable(float cooldownTime)
    : cooldownTime(cooldownTime)
    , lastTimeUsed(-cooldownTime-1.)
    , isBeingUsed(false)
{

}

void Cooldownable::use()
{
    isBeingUsed = true;
}

bool Cooldownable::hasCooldown(float time)
{
    return time - lastTimeUsed < cooldownTime;
}

void Cooldownable::update(float time)
{
    if(isBeingUsed)
    {
        isBeingUsed = false;
        lastTimeUsed = time;
    }
}

float Cooldownable::cooldownTimeRemaining(float time)
{
    return cooldownTime - (time - lastTimeUsed);
}
