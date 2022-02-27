#pragma once

#include <InputController.hpp>
#include <MainMenuState.hpp>
class MenuController;

class HighscoreMenuInputController : public InputController 
{
    MainMenuState *_mainMenuState;
    MenuController *_menuController;

public:
    HighscoreMenuInputController(MainMenuState *mainMenuState, MenuController *menuController);
    void pullEvents() override;
};
