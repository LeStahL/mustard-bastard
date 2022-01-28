#include "MainMenuInputController.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

const double MainMenuInputController::disableTime = .1;

MainMenuInputController::MainMenuInputController(MainMenuState *mainMenuState, MenuController *menuController)
    : _mainMenuState(mainMenuState)
    , _menuController(menuController)
    , _disabled(false)
{
}

void MainMenuInputController::pullEvents() {
    if(_disableClock.getElapsedTime().asSeconds() > disableTime)
    {
        _disabled = false;
        _disableClock.restart();
    }

    if(_disabled) return;
    
    _disabled = true;
    _disableClock.restart();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _mainMenuState->selectIndex((_mainMenuState->selectedIndex() + 1) % 4);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _mainMenuState->selectIndex((_mainMenuState->selectedIndex() + 3) % 4);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if(_mainMenuState->selectedIndex() == 3)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::Exit);
        }
        else if(_mainMenuState->selectedIndex() == 0)
        {
            _menuController->exitCurrentState();
            _menuController->enterState(MenuState::MenuType::Game);
        }
    }
}
