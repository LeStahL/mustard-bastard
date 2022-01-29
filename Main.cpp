#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <stdio.h>

#include <Model.h>
#include <GameLogic.h>
#include <InputController.h>
#include "utility/Animation.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock inputClock;
    sf::Clock animationClock;
    Model model;
    GameLogic gameLogic(model);
    InputController inputController(gameLogic);

    sf::Texture bastardTexture;
    bastardTexture.loadFromFile("assets/bastard.png");

    sf::Sprite bastardSprite;
    bastardSprite.setTexture(bastardTexture);
    Animation bastardAnimation(&bastardSprite, .1);
    for(int i=0; i<4; ++i)
        bastardAnimation.addFrame(96*i, 0, 96, 160);
    
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

        bastardAnimation.update(animationClock.getElapsedTime().asSeconds());
        window.draw(bastardSprite);

        window.display();
    }

    return 0;
}
