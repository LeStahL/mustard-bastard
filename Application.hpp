#pragma once

#include <SFML/Window.hpp>

#include <MenuController.hpp>
#include <GameController.hpp>
#include <MusicPlayer.hpp>

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

    MusicPlayer musicPlayer;

    public:
    Application(sf::RenderWindow *window);
    Application(sf::RenderWindow *windew, bool qm_quickdevel);
    void run();

    void startGame();
    void exitGame();
};
