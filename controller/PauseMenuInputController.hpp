#pragma once

#include <InputController.hpp>
#include <PauseMenuState.hpp>
class GameController;

class PauseMenuInputController : public InputController 
{
    PauseMenuState *_PauseMenuState;
    GameController *_gameController;

public:
    PauseMenuInputController(PauseMenuState *PauseMenuState, GameController *gameController);
    void pullEvents() override;

    static const double disableTime;
};
