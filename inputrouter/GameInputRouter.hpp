#pragma once

#include <GameLogic.hpp>
#include <InputRouter.hpp>

class GameController;

class GameInputRouter : public InputRouter {
private:
    GameLogic& gameLogic;
    GameController *gameController;

public:
    GameInputRouter(GameLogic& gameLogic, GameController *gameController);
    void pullEvents() override;
};
