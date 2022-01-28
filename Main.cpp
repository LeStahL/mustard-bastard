#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <stdio.h>

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

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mustard Bastard / 2022 Global Game Jam / Team210 at work (hardly)", sf::Style::Default, settings);

    sf::Clock inputClock;
    sf::Clock gameClock;
    Model model;
    GameLogic gameLogic(model);
    GameInputController gameInputController(gameLogic);
    GameView gameView(&window, model.getGameViewModel());

    ViewStuff viewStuff(&window);
    
    sf::Texture bastardTexture;
    bastardTexture.loadFromFile("assets/bastard.png");

    sf::Sprite bastardSprite;
    bastardSprite.setTexture(bastardTexture);
    Animation bastardAnimation(&bastardSprite, .1);
    for(int i=0; i<4; ++i)
        bastardAnimation.addFrame(96*i, 0, 96, 160);

    MenuState menuState;
    MainMenuState mainMenuState;
    MainMenuView mainMenuView(&window, &menuState, &mainMenuState);
    MenuController menuController(&menuState, &window, &mainMenuState, &mainMenuView, &gameView, &viewStuff);
    MainMenuInputController mainMenuInputController(&mainMenuState, &menuController);
    menuController.setGameInputController(&gameInputController);
    menuController.setMainMenuInputController(&mainMenuInputController);
    menuController.enterState(MenuState::MenuType::MainMenu);

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
