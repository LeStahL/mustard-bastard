#include <map>
#include <InputController.h>
#include <SFML/Window.hpp>
#include <const.h>

InputController::InputController(GameLogic& gameLogic) :
        gameLogic(gameLogic) {
}

enum Key
{
    Up,
    Left,
    Down,
    Right,
    Attack,
    Retreat
};

std::map<int, std::map<Key, sf::Keyboard::Key>> PlayerKey = {

    { 0, {
        { Key::Up, sf::Keyboard::Up },
        { Key::Left, sf::Keyboard::Key::Left },
        { Key::Down, sf::Keyboard::Down },
        { Key::Right, sf::Keyboard::Key::Right },
        { Key::Attack, sf::Keyboard::Key::Period },
        { Key::Retreat, sf::Keyboard::Key::Comma },
    } },

    { 1, {
        { Key::Up, sf::Keyboard::W },
        { Key::Left, sf::Keyboard::Key::A },
        { Key::Down, sf::Keyboard::S },
        { Key::Right, sf::Keyboard::Key::D },
        { Key::Attack, sf::Keyboard::Key::C },
        { Key::Retreat, sf::Keyboard::Key::X }
    } }
};

void InputController::pullEvents() {

    for (int p = 0; p < gameLogic.nPlayers(); p++)
    {
        int x_sign = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Right])
            ? 1
            : sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Left])
            ? -1
            : 0;

        gameLogic.move_x(p, x_sign);
    }
}