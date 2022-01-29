#pragma once

#include "MenuState.hpp"
#include "View.hpp"
#include "MainMenuView.hpp"
#include "GameView.hpp"
#include "GameInputController.hpp"
#include "MainMenuInputController.hpp"
#include "InputController.hpp"

class MenuController
{
    MenuState *_state;
    View *_view;
    sf::RenderWindow *_window;
    MainMenuState *_mainMenuState;
    MainMenuView *_mainMenuView;
    GameView *_gameView;
    GameInputController *_gameInputController;
    MainMenuInputController *_mainMenuInputController;
    InputController *_inputController;

    public:
    MenuController(MenuState *state, sf::RenderWindow *window, MainMenuState *mainMenuState, MainMenuView *mainMenuView, GameView *gameView);
    void setMainMenuInputController(MainMenuInputController *mainMenuInputController);
    void setGameInputController(GameInputController *gameInputController);
    bool canEnterState(MenuState::MenuType type);
    bool exitCurrentState();
    bool enterState(MenuState::MenuType type);

    bool draw(double time);
};
