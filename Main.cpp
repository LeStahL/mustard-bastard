#include <SFML/Window.hpp>

#include <stdio.h>

#include <Model.h>

int main()
{
    printf("Hi.");
    sf::Window window(sf::VideoMode(800, 600), "My window");
    printf("Created window.\n");

    // create model and print entitiy ids for testing
    Model model;
    for(auto it = std::begin(model.getEntities()); it != std::end(model.getEntities()); ++it) {
        printf("%d\n", it->id);
    }

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
