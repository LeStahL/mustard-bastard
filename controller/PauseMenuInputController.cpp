#include "PauseMenuInputController.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

const double PauseMenuInputController::disableTime = .15;

PauseMenuInputController::PauseMenuInputController(PauseMenuState *PauseMenuState, MenuController *menuController)
    : _PauseMenuState(PauseMenuState)
    , _menuController(menuController)
    , _disabled(false)
{
}

void PauseMenuInputController::pullEvents() {
    if(_disableClock.getElapsedTime().asSeconds() > disableTime)
    {
        _disabled = false;
        _disableClock.restart();
    }

    if(_disabled) return;
    
    _disabled = true;
    _disableClock.restart();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _PauseMenuState->selectIndex((_PauseMenuState->selectedIndex() + 1) % 2);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _PauseMenuState->selectIndex((_PauseMenuState->selectedIndex() + 1) % 2);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
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
