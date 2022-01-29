#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <stdio.h>
#include <iostream>

#include <Model.h>
#include <GameLogic.h>
#include <InputController.hpp>
#include "Animation.hpp"
#include "View.hpp"
#include "MainMenuView.hpp"
#include "MenuController.hpp"
#include "MainMenuInputController.hpp"
#include "GameInputController.hpp"
#include <ViewStuff.h>
#include <const.h>
#include <GameView.hpp>
#include "HighscoreList.hpp"

constexpr bool QM_QUICKDEVEL = false;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mustard Bastard / 2022 Global Game Jam / Team210 at work (hardly)", sf::Style::Default, settings);

    sf::Clock inputClock;
    sf::Clock gameClock;
    sf::Clock animationClock;

    std::cout << "Init ViewStuff?" << std::endl;
    ViewStuff viewStuff(&window);
    std::cout << "Init Model?" << std::endl;
    Model model;
    std::cout << "Init GameViewModel?" << std::endl;
    GameViewModel gameViewModel(&viewStuff, &model);
    std::cout << "Init GameLogic?" << std::endl;
    GameLogic gameLogic(&model);
    std::cout << "Init GameInputContrller?" << std::endl;
    GameInputController gameInputController(gameLogic);
    std::cout << "Init GameView?" << std::endl;
    GameView gameView(&window, gameViewModel);
    std::cout << "Survived initialization." << std::endl;

    MenuState menuState;
    MainMenuState mainMenuState;
    MainMenuView mainMenuView(&window, &menuState, &mainMenuState);
    HighscoreList highscoreList;
    HighscoreMenuView highscoreMenuView(&window, &menuState, &highscoreList);
    MenuController menuController(&menuState, &window, &mainMenuState, &mainMenuView, &gameView, &highscoreList, &highscoreMenuView);
    MainMenuInputController mainMenuInputController(&mainMenuState, &menuController);
    HighscoreMenuInputController highscoreMenuInputController(&mainMenuState, &menuController);
    menuController.setGameInputController(&gameInputController);
    menuController.setMainMenuInputController(&mainMenuInputController);
    menuController.setHighscoreMenuInputController(&highscoreMenuInputController);
    menuController.enterState(QM_QUICKDEVEL ? MenuState::Game : MenuState::MenuType::MainMenu);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        gameLogic.update(inputClock.getElapsedTime().asSeconds());
        inputClock.restart();

        window.clear(sf::Color::Black);

        menuController.draw(gameClock.getElapsedTime().asSeconds());

        window.display();
    }

    return 0;
}
