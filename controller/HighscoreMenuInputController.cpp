#include "HighscoreMenuInputController.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

HighscoreMenuInputController::HighscoreMenuInputController(MainMenuState *mainMenuState, MenuController *menuController)
    : _mainMenuState(mainMenuState)
    , _menuController(menuController)
{
}

void HighscoreMenuInputController::pullEvents() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _menuController->exitCurrentState();
        _menuController->enterState(MenuState::MenuType::MainMenu);
    }
}
