#pragma once

#include <SFML/System.hpp>

#include "MenuState.hpp"
#include "View.hpp"
#include "InputRouter.hpp"

#include "MainMenuState.hpp"
#include "MainMenuView.hpp"
#include "MainMenuInputRouter.hpp"

#include "HighscoreList.hpp"
#include "HighscoreMenuView.hpp"
#include "HighscoreMenuInputRouter.hpp"

class Application;

class MenuController
{
    private:
    sf::RenderWindow *_window;
    sf::Clock _menuClock;
    Application *_application;

    MenuState _menuState;
    View *_view;
    InputRouter *_inputRouter;

    // main menu
    MainMenuState _mainMenuState;
    MainMenuView _mainMenuView;
    MainMenuInputRouter _mainMenuInputRouter;

    // TODO: settings menu

    // highscore menu
    HighscoreList _highscoreList;
    HighscoreMenuView _highscoreMenuView;
    HighscoreMenuInputRouter _highscoreMenuInputRouter;

    public:
    MenuController(sf::RenderWindow *window, Application *application);
    bool canEnterState(MenuState::MenuType type);
    bool exitCurrentState();
    bool enterState(MenuState::MenuType type);

    bool update();
};
