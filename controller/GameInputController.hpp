#pragma once

#include <GameLogic.h>
#include "InputController.hpp"
class GameController;

class GameInputController : public InputController {
private:
    GameLogic& gameLogic;
    GameController *gameController;

public:
    GameInputController(GameLogic& gameLogic, GameController *gameController);
    void pullEvents() override;
};
