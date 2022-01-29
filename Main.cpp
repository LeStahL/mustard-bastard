#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <stdio.h>

#include <Model.h>
#include <GameLogic.h>
#include <InputController.h>
#include <GameView.hpp>
#include "utility/Animation.hpp"
#include <ViewStuff.h>
#include <const.h>

int main()
{
    printf("Hi.");
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mustard Bastard / 2022 Global Game Jam / Team210 at work (hardly)", sf::Style::Default, settings);
    printf("Created window.\n");

    sf::Clock inputClock;
    sf::Clock animationClock;
    Model model;
    GameLogic gameLogic(model);
    InputController inputController(gameLogic);
    GameView gameView(&window, model.getGameViewModel());

    ViewStuff viewStuff(&window);
    gameView.setUp();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        inputController.pullEvents();
        gameLogic.update(inputClock.getElapsedTime().asSeconds());
        inputClock.restart();

        window.clear(sf::Color::Black);

        
        gameView.draw(animationClock.getElapsedTime().asSeconds());
        viewStuff.DrawBackground();

        window.display();
    }

    return 0;
}
