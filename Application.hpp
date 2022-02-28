#pragma once

#include <SFML/Window.hpp>

#include <MenuController.hpp>
#include <GameController.hpp>

class Application {
    private:
    enum class ApplicationState {
        MainMenu,
        InGame
    };

    sf::RenderWindow *window;
    ApplicationState applicationState;

    MenuController menuController;
    GameController gameController;

    public:
    Application(sf::RenderWindow *window);
    void run();

    void startGame();
    void exitGame();
};
