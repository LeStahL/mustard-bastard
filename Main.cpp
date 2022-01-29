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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock inputClock;
    sf::Clock animationClock;
    Model model;
    GameLogic gameLogic(model);
    InputController inputController(gameLogic);
    GameView gameView(&window, model.getGameViewModel());

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

        window.display();
    }

    return 0;
}
