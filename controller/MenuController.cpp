#include "MenuController.hpp"

#include <iostream>

MenuController::MenuController(MenuState *state, sf::RenderWindow *window, MainMenuState *mainMenuState, MainMenuView *mainMenuView, GameView *gameView, HighscoreList *highscoreList, HighscoreMenuView *highscoreMenuView, MusicPlayer *musicPlayer, HeadsUpDisplayView *headsUpDisplayView, GameLogic *gameLogic)
    : _state(state)
    , _window(window)
    , _mainMenuState(mainMenuState)
    , _mainMenuView(mainMenuView)
    , _gameView(gameView)
    , _view(nullptr)
    , _inputController(nullptr)
    , _highscoreList(highscoreList)
    , _highscoreMenuView(highscoreMenuView)
    , _musicPlayer(musicPlayer)
    , _headsUpDisplayView(headsUpDisplayView)
    , _gameLogic(gameLogic)
{
}

void MenuController::setGameInputController(GameInputController *gameInputController)
{
    _gameInputController = gameInputController;
}

void MenuController::setPauseMenuInputController(PauseMenuInputController *pauseMenuInputController)
{
    _pauseMenuInputController = pauseMenuInputController;
}

void MenuController::setMainMenuInputController(MainMenuInputController *mainMenuInputController)
{
    _mainMenuInputController = mainMenuInputController;
}

void MenuController::setHighscoreMenuInputController(HighscoreMenuInputController *highscoreMenuInputController)
{
    _highscoreMenuInputController = highscoreMenuInputController;
}

bool MenuController::canEnterState(MenuState::MenuType type)
{
    if(_state->currentType() == type) return false;
    return true;
}

bool MenuController::exitCurrentState()
{
    //if(_view != nullptr) _view->tearDown();
    _musicPlayer->stop();

    switch(_state->currentType())
    {
        case MenuState::MenuType::Game:
        break;
        case MenuState::MenuType::PauseMenu:
        //_headsUpDisplayView->tearDown();
        //_gameView->tearDown();
        // TODO: Reset game, player, level, score state etc
        // TODO: Unload game scene
        break;

        case MenuState::Loading:
        break;

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
    _inputController = nullptr;

    return false;
}

bool MenuController::enterState(MenuState::MenuType type)
{
    _state->setType(type);
    switch(type)
    {
        case MenuState::MenuType::Exit:
        _window->close();
        return true;

        case MenuState::MenuType::Loading:
        _headsUpDisplayView->setUp();
        _gameView->setUp();
        enterState(MenuState::Game);
        return true;

        case MenuState::MenuType::Game:
        _view = _gameView;
        _inputController = _gameInputController;
        _musicPlayer->playSound(MusicPlayer::SoundType::GameSound);
        _gameLogic->resumeGame();
        return true;

        case MenuState::MenuType::HighScoreMenu:
        _view = _highscoreMenuView;
        _inputController = _highscoreMenuInputController;
        _view->setUp();
        break;

        case MenuState::MenuType::MainMenu:    
        _view = _mainMenuView;
        _inputController = _mainMenuInputController;
        _view->setUp();
        return true;

        case MenuState::MenuType::PauseMenu:
        _view = _gameView;
        _inputController = _pauseMenuInputController;
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

    bool result = false;
    if(_view != nullptr) result = _view->draw(time);

    if(_state->currentType() == MenuState::MenuType::Game)
        _headsUpDisplayView->draw(time);

    return result;
}
