#pragma once

#include "MenuState.hpp"
#include "View.hpp"
#include "MainMenuView.hpp"
#include "GameView.hpp"
#include "GameInputController.hpp"
#include "MainMenuInputController.hpp"
#include "PauseMenuInputController.hpp"
#include "InputController.hpp"
#include "HighscoreList.hpp"
#include "HighscoreMenuInputController.hpp"
#include "HighscoreMenuView.hpp"
#include "MusicPlayer.hpp"
#include "HeadsUpDisplayView.hpp"
#include <GameLogic.h>

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
    PauseMenuInputController *_pauseMenuInputController;
    InputController *_inputController;
    HighscoreMenuView *_highscoreMenuView;
    HighscoreMenuInputController *_highscoreMenuInputController;
    HighscoreList *_highscoreList;
    MusicPlayer *_musicPlayer;
    HeadsUpDisplayView *_headsUpDisplayView;
    GameLogic *_gameLogic;

    public:
    MenuController(MenuState *state, sf::RenderWindow *window, MainMenuState *mainMenuState, MainMenuView *mainMenuView, GameView *gameView, HighscoreList *highscoreList, HighscoreMenuView *highscoreMenuView, MusicPlayer *musicPlayer, HeadsUpDisplayView *headsUpDisplayView, GameLogic *gameLogic);
    void setMainMenuInputController(MainMenuInputController *mainMenuInputController);
    void setGameInputController(GameInputController *gameInputController);
    void setPauseMenuInputController(PauseMenuInputController *pauseMenuInputController);
    void setHighscoreMenuInputController(HighscoreMenuInputController *highscoreMenuInputController);
    bool canEnterState(MenuState::MenuType type);
    bool exitCurrentState();
    bool enterState(MenuState::MenuType type);

    bool draw(double time);
};
