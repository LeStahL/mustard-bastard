#pragma once

class Cooldownable
{
    public:
    Cooldownable(float cooldownTime);
    float cooldownTime;
    float lastTimeUsed;
    bool isBeingUsed;

    void use();
    bool hasCooldown(float time);
    float cooldownTimeRemaining(float time);

    void update(float time);
};