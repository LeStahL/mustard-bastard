#pragma once

#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>

class InputController {
protected:
    static sf::Keyboard::Key _pressedKey;
    static sf::Clock _disableClock;
public:
    InputController() = default;
    virtual void pullEvents() = 0;
};
