#include <Application.hpp>

Application::Application(sf::RenderWindow *window, bool qm_quickdevel) :
    window(window),
    applicationState(ApplicationState::MainMenu),
    menuController(window, this),
    gameController(window, this),
    musicPlayer(qm_quickdevel)
{
    if(qm_quickdevel)
        startGame();
}

Application::Application(sf::RenderWindow *window) :
    Application(window, false)
{

}

void Application::run()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                //|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                window->close();
        }

        window->clear(sf::Color::Black);

        switch(applicationState) {
        case ApplicationState::MainMenu:
            menuController.update();
            break;
        case ApplicationState::InGame:
            gameController.update();
            break;
        };

        window->display();
    }
}

void Application::startGame()
{
    applicationState = ApplicationState::InGame;
    gameController.startGame();
    musicPlayer.playSound(MusicPlayer::SoundType::GameSound);
}

void Application::exitGame()
{
    applicationState = ApplicationState::MainMenu;
    menuController.enterState(MenuState::MenuType::MainMenu);
    musicPlayer.stop();
}
