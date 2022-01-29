#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <stdio.h>

#include <Model.h>
#include <GameLogic.h>
#include <InputController.h>

int main()
{
    printf("Hi.");
    sf::Window window(sf::VideoMode(960, 540), "My window");
    printf("Created window.\n");

    sf::Clock clock;
    Model model;
    GameLogic gameLogic(model);
    InputController inputController(gameLogic);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Time time = clock.getElapsedTime();
            clock.restart();
            inputController.pullEvents();
            gameLogic.update(time.asSeconds());
        }
    }

    return 0;
}
