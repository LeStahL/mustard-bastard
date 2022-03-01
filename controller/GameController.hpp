#pragma once

#include <vector>

#include <SFML/System/Clock.hpp>

#include <View.hpp>
#include <InputRouter.hpp>

#include <Model.h>
#include <GameView.hpp>
#include <HeadsUpDisplayView.hpp>
#include <GameInputRouter.hpp>
#include <GameLogic.h>

#include <PauseMenuState.hpp>
#include <PauseMenuView.hpp>
#include <PauseMenuInputRouter.hpp>

class Application;

class GameController {

    private:
    Application *application;
    std::vector<View*> viewList;
    InputRouter *inputRouter;

    sf::Clock continuousTimeClock;
    sf::Clock elapsedTimeClock;

    // game
    Model model;
    GameView gameView;
    HeadsUpDisplayView headsUpDisplayView;
    GameInputRouter gameInputRouter;
    GameLogic gameLogic;

    // pause menu
    PauseMenuState pauseMenuState;
    PauseMenuView pauseMenuView;
    PauseMenuInputRouter pauseMenuInputRouter;

    public:
    GameController(sf::RenderWindow *window, Application *application);

    void update();

    void startGame();
    void exitGame();
    void pauseGame();
    void resumeGame();
};
