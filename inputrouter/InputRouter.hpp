#pragma once

#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

class InputRouter {
protected:
    static sf::Keyboard::Key _pressedKey;
    static sf::Clock _disableClock;
public:
    InputRouter() = default;
    virtual void pullEvents() = 0;
};
