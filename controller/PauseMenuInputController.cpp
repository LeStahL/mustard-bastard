#include "PauseMenuInputController.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

const double PauseMenuInputController::disableTime = .15;

PauseMenuInputController::PauseMenuInputController(PauseMenuState *PauseMenuState, MenuController *menuController)
    : _PauseMenuState(PauseMenuState)
    , _menuController(menuController)
{
    _pressedKey = sf::Keyboard::Unknown;
}

void PauseMenuInputController::pullEvents() {
    if(sf::Keyboard::isKeyPressed(_pressedKey) && _disableClock.getElapsedTime().asSeconds() < disableTime) {
        return;
    }
    _pressedKey = sf::Keyboard::Unknown;
    _disableClock.restart();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _pressedKey = sf::Keyboard::Right;
        _PauseMenuState->selectIndex((_PauseMenuState->selectedIndex() + 1) % 2);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _pressedKey = sf::Keyboard::Left;
        _PauseMenuState->selectIndex((_PauseMenuState->selectedIndex() + 1) % 2);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        _pressedKey = sf::Keyboard::Enter;
        if(_PauseMenuState->selectedIndex() == 0)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::Game);
        }
        else if(_PauseMenuState->selectedIndex() == 1)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::MainMenu);
        }
    }
}
