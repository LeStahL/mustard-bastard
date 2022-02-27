#include <map>
#include <GameInputController.hpp>
#include <SFML/Window.hpp>
#include <const.h>
#include <MenuController.hpp>

GameInputController::GameInputController(GameLogic& gameLogic, MenuController *menuController) :
        gameLogic(gameLogic),
        menuController(menuController) {
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

void GameInputController::pullEvents() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameLogic.pauseGame();
        menuController->enterState(MenuState::PauseMenu);
        return;
    }

    for (int p = 0; p < gameLogic.nPlayers(); p++)
    {
        bool right = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Right]);
        bool left = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Left]);
        bool up = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Up]);
        bool down = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Down]);
        bool attack = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Attack]);
        bool retreat = sf::Keyboard::isKeyPressed(PlayerKey[p][Key::Retreat]);

        int x_sign = (right && !left) ? 1 : (left && !right) ? -1 : 0;
        int z_sign = (up && !down) ? 1 : (down && !up) ? -1 : 0;

        gameLogic.move_player(p, x_sign, retreat, z_sign, attack);
    }
}
