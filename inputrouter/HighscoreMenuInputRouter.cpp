#include "HighscoreMenuInputRouter.hpp"
#include "MenuController.hpp"
#include <SFML/Window.hpp>

HighscoreMenuInputRouter::HighscoreMenuInputRouter(MainMenuState *mainMenuState, MenuController *menuController)
    : _mainMenuState(mainMenuState)
    , _menuController(menuController)
{
}

void HighscoreMenuInputRouter::pullEvents() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _menuController->exitCurrentState();
        _menuController->enterState(MenuState::MenuType::MainMenu);
    }
}
