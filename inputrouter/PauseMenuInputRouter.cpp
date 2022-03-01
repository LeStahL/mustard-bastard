#include "PauseMenuInputRouter.hpp"
#include <GameController.hpp>
#include <SFML/Window.hpp>

const double PauseMenuInputRouter::disableTime = .15;

PauseMenuInputRouter::PauseMenuInputRouter(PauseMenuState *pauseMenuState, GameController *gameController)
    : _PauseMenuState(pauseMenuState)
    , _gameController(gameController)
{
    _pressedKey = sf::Keyboard::Unknown;
}

void PauseMenuInputRouter::pullEvents() {
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
            _gameController->resumeGame();
        }
        else if(_PauseMenuState->selectedIndex() == 1)
        {
            _gameController->exitGame();
        }
    }
}
