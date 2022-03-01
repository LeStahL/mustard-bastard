#include <stdio.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <Application.hpp>

constexpr bool QM_QUICKDEVEL = false;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mustard Bastard / 2022 Global Game Jam / Team210 at work (hardly)", sf::Style::Default, settings);

    Application application(&window, QM_QUICKDEVEL);
    application.run();

    return 0;
}
