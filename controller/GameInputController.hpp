#pragma once

#include <GameLogic.h>
#include <GameInputController.hpp>
#include "InputController.hpp"

class GameInputController : public InputController {
private:
    GameLogic& gameLogic;

public:
    GameInputController(GameLogic& GameLogic);
    void pullEvents() override;
};
