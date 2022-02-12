#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
    std::vector<sf::IntRect> _frameRectangles;
    double _delay;
    double _initialTimeOffset;
    sf::Sprite *_sprite;

    public:
    Animation(sf::Sprite *sprite, double delay, double initialTimeOffset);
    void addFrame(int left, int top, int width, int height);
    void update(double elapsedTime);
    void setFrameDelay(double delay);

    sf::Sprite *sprite();
};
