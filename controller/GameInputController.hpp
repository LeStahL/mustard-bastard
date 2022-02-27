#pragma once

#include <GameLogic.h>
#include "InputController.hpp"
class MenuController;

class GameInputController : public InputController {
private:
    GameLogic& gameLogic;
    MenuController  *menuController;

public:
    GameInputController(GameLogic& gameLogic, MenuController *menuController);
    void pullEvents() override;
};
