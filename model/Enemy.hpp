#pragma once

#include <Entity.h>
#include <IsDrawable.hpp>

class Enemy : public Entity, public IsDrawable {
    public:
    float health;
    float speed;

    Enemy(int graphicId, WorldPosition position);
};