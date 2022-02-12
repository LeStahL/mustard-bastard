#include "Animation.hpp"

Animation::Animation(sf::Sprite *sprite, double delay, double initialTimeOffset)
    : _sprite(sprite)
    , _delay(delay)
    , _initialTimeOffset(initialTimeOffset)
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
    _sprite->setTextureRect(_frameRectangles.at(int((_initialTimeOffset + elapsedTime)/_delay) % _frameRectangles.size()));
}

void Animation::setFrameDelay(double delay)
{
    _delay = delay;
}

sf::Sprite *Animation::sprite()
{
    return _sprite;
}
