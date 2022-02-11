#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <AttackState.hpp>

#include <string>

enum PlayerState {
    Standing,
    Walking,
    Attacking,
    Warping
};

class Player : public Entity {
    public:
    PlayerState state;
    float move_z_cooldown;
    AttackState attack_state;
    float power = 1;
    float health = .5;
    long points = 0;
    std::string name;

    const float HALFWIDTH = 50;
    const float WARP_TIME = 4;

    private:
    float warp_timer;

    public:
    Player(std::string name, int graphicId, WorldPosition position, WorldOrientation orientation);

    Player(std::string name, int graphicId, WorldPosition position) : Player(name, graphicId, position, WorldOrientation())
    {}

    std::pair<float, float> getCollisionXInterval() override;
    bool isCollisionActive() override;

    void update(float elapsed);
    void beginWarp();
    void endWarp();
//    bool onCollisionWith(Entity* other, void (*callback)(Entity* other)) override;
};

#endif /* PLAYER_H */