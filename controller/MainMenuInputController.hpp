#pragma once

#include <InputController.hpp>
#include <MainMenuState.hpp>
class MenuController;

class MainMenuInputController : public InputController 
{
    MainMenuState *_mainMenuState;
    MenuController *_menuController;

public:
    MainMenuInputController(MainMenuState *mainMenuState, MenuController *menuController);
    void pullEvents() override;

    static const double disableTime;
};
