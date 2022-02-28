#pragma once

#include <vector>

#include <SFML/System/Clock.hpp>

#include <View.hpp>
#include <InputController.hpp>

#include <Model.h>
#include <GameView.hpp>
#include <HeadsUpDisplayView.hpp>
#include <GameInputController.hpp>
#include <GameLogic.h>

#include <PauseMenuState.hpp>
#include <PauseMenuView.hpp>
#include <PauseMenuInputController.hpp>

class Application;

class GameController {

    private:
    Application *application;
    std::vector<View*> viewList;
    InputController *inputController;

    sf::Clock continuousTimeClock;
    sf::Clock elapsedTimeClock;

    // game
    Model model;
    GameView gameView;
    HeadsUpDisplayView headsUpDisplayView;
    GameInputController gameInputController;
    GameLogic gameLogic;

    // pause menu
    PauseMenuState pauseMenuState;
    PauseMenuView pauseMenuView;
    PauseMenuInputController pauseMenuInputController;

    public:
    GameController(sf::RenderWindow *window, Application *application);

    void update();

    void startGame();
    void exitGame();
    void pauseGame();
    void resumeGame();
};
