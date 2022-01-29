#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <GameLogic.h>

class InputController {
private:
    GameLogic& gameLogic;

public:
    InputController(GameLogic& GameLogic);
    void pullEvents();
};

#endif /* INPUT_CONTROLLER_H */