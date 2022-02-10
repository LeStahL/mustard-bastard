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
#include <const.h>
#include <GameView.hpp>
#include "HighscoreList.hpp"
#include "MusicPlayer.hpp"
#include "HeadsUpDisplayView.hpp"

constexpr bool QM_QUICKDEVEL = true;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mustard Bastard / 2022 Global Game Jam / Team210 at work (hardly)", sf::Style::Default, settings);

    sf::Clock inputClock;
    sf::Clock gameClock;
    sf::Clock animationClock;

    std::cout << "Init Model?" << std::endl;
    Model model;
    std::cout << "Init GameLogic?" << std::endl;
    GameLogic gameLogic(&model);
    std::cout << "Init GameInputContrller?" << std::endl;
    GameInputController gameInputController(gameLogic);
    std::cout << "Init GameView?" << std::endl;
    GameView gameView(&window, model);
    std::cout << "Survived initialization." << std::endl;

    MusicPlayer musicPlayer;

    MenuState menuState;
    
    MainMenuState mainMenuState;
    MainMenuView mainMenuView(&window, &menuState, &mainMenuState);
    
    HighscoreList highscoreList;
    HighscoreMenuView highscoreMenuView(&window, &menuState, &highscoreList);
    
    Player *player1 = nullptr;
    Player *player2 = nullptr;
    if(model.getNumberOfPlayers() >= 1)
        player1 = model.getPlayer(0);
    if(model.getNumberOfPlayers() == 2)
        player2 = model.getPlayer(1);

    HeadsUpDisplayView headsUpDisplayView(&window, &menuState, player1, player2);

    MenuController menuController(&menuState, &window, &mainMenuState, &mainMenuView, &gameView, &highscoreList, &highscoreMenuView, &musicPlayer, &headsUpDisplayView);
    
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
            if (event.type == sf::Event::Closed
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
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
