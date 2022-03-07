#pragma once

class Cooldown {
private:
    float cooldown;

public:
    Cooldown(float cooldown) : cooldown(cooldown) {}
    Cooldown() : Cooldown(0.0f) {}

    float getCooldown() const { return cooldown; }
    void setCooldown(const float cooldown) { this->cooldown = cooldown > 0.0f ? cooldown : 0.0f; }
    void coolDownBy(const float elapsedTime) { setCooldown(cooldown - elapsedTime); }
    bool cooledDown() const { return cooldown < 1e-3f; }
};
