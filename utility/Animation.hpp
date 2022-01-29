#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
    std::vector<sf::IntRect> _frameRectangles;
    double _delay;
    sf::Sprite *_sprite;

    public:
    Animation(sf::Sprite *sprite, double delay);
    void addFrame(int left, int top, int width, int height);
    void update(double elapsedTime);
};
