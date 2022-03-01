#include "MenuController.hpp"
#include <Application.hpp>

MenuController::MenuController(sf::RenderWindow *window, Application *application) :
    _window(window),
    _application(application),
    _view(&_mainMenuView),
    _inputRouter(&_mainMenuInputRouter),
    _mainMenuView(window, &_menuState, &_mainMenuState),
    _mainMenuInputRouter(&_mainMenuState, this),
    _highscoreMenuView(window, &_menuState, &_highscoreList),
    _highscoreMenuInputRouter(&_mainMenuState, this)
{
}

bool MenuController::canEnterState(MenuState::MenuType type)
{
    if(_menuState.currentType() == type) return false;
    return true;
}

bool MenuController::exitCurrentState()
{
    //if(_view != nullptr) _view->tearDown();

    switch(_menuState.currentType())
    {
        case MenuState::MenuType::HighScoreMenu:
        break;

        case MenuState::MenuType::MainMenu:
        break;

        case MenuState::MenuType::SettingsMenu:
        break;

        default:
        break;
    }

    _view = nullptr;
    _inputRouter = nullptr;

    return false;
}

bool MenuController::enterState(MenuState::MenuType type)
{
    _menuState.setType(type);
    switch(type)
    {
        case MenuState::MenuType::StartGame:
        _application->startGame();
        return true;

        case MenuState::MenuType::Exit:
        _window->close();
        return true;

        case MenuState::MenuType::HighScoreMenu:
        _view = &_highscoreMenuView;
        _inputRouter = &_highscoreMenuInputRouter;
        _view->setUp();
        break;

        case MenuState::MenuType::MainMenu:    
        _view = &_mainMenuView;
        _inputRouter = &_mainMenuInputRouter;
        _view->setUp();
        return true;

        case MenuState::MenuType::SettingsMenu:
        break;

        default:
        return false;
    }

    return false;
}

bool MenuController::update()
{
    if(_inputRouter != nullptr) _inputRouter->pullEvents();

    bool result = false;
    if(_view != nullptr) result = _view->draw(_menuClock.getElapsedTime().asSeconds());

    return result;
}
