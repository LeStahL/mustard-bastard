#include "MenuController.hpp"

MenuController::MenuController(MenuState *state, sf::RenderWindow *window, MainMenuState *mainMenuState, MainMenuView *mainMenuView, GameView *gameView)
    : _state(state)
    , _window(window)
    , _mainMenuState(mainMenuState)
    , _mainMenuView(mainMenuView)
    , _gameView(gameView)
    , _view(nullptr)
    , _inputController(nullptr)
{
}

void MenuController::setGameInputController(GameInputController *gameInputController)
{
    _gameInputController = gameInputController;
}

void MenuController::setMainMenuInputController(MainMenuInputController *mainMenuInputController)
{
    _mainMenuInputController = mainMenuInputController;
}

bool MenuController::canEnterState(MenuState::MenuType type)
{
    if(_state->currentType() == type) return false;
    return true;
}

bool MenuController::exitCurrentState()
{
    
    switch(_state->currentType())
    {
        case MenuState::MenuType::Game:
        // TODO: Reset game, player, level, score state etc
        // TODO: Unload game scene
        if(_view != nullptr) _view->tearDown();
        break;

        case MenuState::MenuType::HighScoreMenu:
        break;

        case MenuState::MenuType::MainMenu:
        break;

        case MenuState::MenuType::PauseMenu:
        break;

        case MenuState::MenuType::SettingsMenu:
        break;

        default:
        break;
    }

    _view = nullptr;
    _inputController = nullptr;

    return false;
}

bool MenuController::enterState(MenuState::MenuType type)
{
    switch(type)
    {
        case MenuState::MenuType::Exit:
        _window->close();
        return true;

        case MenuState::MenuType::Game:
        // TODO: Start game
        _view = _gameView;
        _inputController = _gameInputController;
        _view->setUp();
        return true;

        case MenuState::MenuType::HighScoreMenu:
        break;

        case MenuState::MenuType::MainMenu:
        _view = _mainMenuView;
        _inputController = _mainMenuInputController;
        return true;

        case MenuState::MenuType::PauseMenu:
        break;

        case MenuState::MenuType::SettingsMenu:
        break;

        default:
        return false;
    }

    return false;
}

bool MenuController::draw(double time)
{
    if(_inputController != nullptr) _inputController->pullEvents();

    if(_view != nullptr) return _view->draw(time);

    return false;
}
