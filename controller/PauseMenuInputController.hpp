#pragma once

#include <InputController.hpp>
#include <PauseMenuState.hpp>
class MenuController;

class PauseMenuInputController : public InputController 
{
    PauseMenuState *_PauseMenuState;
    MenuController *_menuController;

public:
    PauseMenuInputController(PauseMenuState *PauseMenuState, MenuController *menuController);
    void pullEvents() override;

    static const double disableTime;
};
