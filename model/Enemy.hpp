#pragma once

#include <IsDrawable.hpp>

class Enemy : public IsDrawable {
    public:
    float health;
    float speed;

    Enemy(int graphicId, WorldPosition position);
};