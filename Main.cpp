#include <SFML/Window.hpp>

#include <stdio.h>

int main()
{
    printf("Hi.");
    sf::Window window(sf::VideoMode(800, 600), "My window");
    printf("Created window.");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}
