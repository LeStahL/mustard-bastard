#pragma once

#include <InputRouter.hpp>
#include <PauseMenuState.hpp>
class GameController;

class PauseMenuInputRouter : public InputRouter
{
    PauseMenuState *_PauseMenuState;
    GameController *_gameController;

public:
    PauseMenuInputRouter(PauseMenuState *PauseMenuState, GameController *gameController);
    void pullEvents() override;

    static const double disableTime;
};
