#include "Animation.hpp"

Animation::Animation(sf::Sprite *sprite, double delay)
    : _sprite(sprite)
    , _delay(delay)
{
}

void Animation::addFrame(int left, int top, int width, int height)
{
    sf::IntRect rect;
    rect.left = left;
    rect.top = top;
    rect.width = width;
    rect.height = height;
    _frameRectangles.push_back(rect);
}

void Animation::update(double elapsedTime) 
{
    _sprite->setTextureRect(_frameRectangles.at(int(elapsedTime/_delay) % _frameRectangles.size()));
}