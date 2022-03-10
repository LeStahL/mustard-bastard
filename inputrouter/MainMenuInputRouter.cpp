#include "MainMenuInputRouter.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

const double MainMenuInputRouter::disableTime = .15;

MainMenuInputRouter::MainMenuInputRouter(MainMenuState *mainMenuState, MenuController *menuController)
    : _mainMenuState(mainMenuState)
    , _menuController(menuController)
{
    _pressedKey = sf::Keyboard::Unknown;
}

void MainMenuInputRouter::pullEvents() {
    if(sf::Keyboard::isKeyPressed(_pressedKey) && _disableClock.getElapsedTime().asSeconds() < disableTime) {
        return;
    }
    _pressedKey = sf::Keyboard::Unknown;
    _disableClock.restart();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _pressedKey = sf::Keyboard::Down;
        _mainMenuState->selectIndex((_mainMenuState->selectedIndex() + 1) % 4);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _pressedKey = sf::Keyboard::Up;
        _mainMenuState->selectIndex((_mainMenuState->selectedIndex() + 3) % 4);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        _pressedKey = sf::Keyboard::Enter;
        if(_mainMenuState->selectedIndex() == 3)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::Exit);
        }
        else if(_mainMenuState->selectedIndex() == 2)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::HighScoreMenu);
        }
        else if(_mainMenuState->selectedIndex() == 0)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::StartGame);
        }
    }
}
