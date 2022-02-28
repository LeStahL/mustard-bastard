#pragma once

#include <SFML/System.hpp>

#include "MenuState.hpp"
#include "View.hpp"
#include "InputController.hpp"

#include "MainMenuState.hpp"
#include "MainMenuView.hpp"
#include "MainMenuInputController.hpp"

#include "HighscoreList.hpp"
#include "HighscoreMenuView.hpp"
#include "HighscoreMenuInputController.hpp"

class Application;

class MenuController
{
    private:
    sf::RenderWindow *_window;
    sf::Clock _menuClock;
    Application *_application;

    MenuState _menuState;
    View *_view;
    InputController *_inputController;

    // main menu
    MainMenuState _mainMenuState;
    MainMenuView _mainMenuView;
    MainMenuInputController _mainMenuInputController;

    // TODO: settings menu

    // highscore menu
    HighscoreList _highscoreList;
    HighscoreMenuView _highscoreMenuView;
    HighscoreMenuInputController _highscoreMenuInputController;

    public:
    MenuController(sf::RenderWindow *window, Application *application);
    bool canEnterState(MenuState::MenuType type);
    bool exitCurrentState();
    bool enterState(MenuState::MenuType type);

    bool update();
};
