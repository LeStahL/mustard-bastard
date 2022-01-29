#include <GameLogic.h>

GameLogic::GameLogic(Model& model) :
        model(model),
        moveState(0) {
}

void GameLogic::update(int timeElapsed) {
    updatePlayer(timeElapsed);
}

void GameLogic::moveForward() {
    moveState = 1;
}

void GameLogic::moveBackward() {
    moveState = -1;
}

void GameLogic::updatePlayer(int timeElapsed) {
    model.getPlayer().position.x = PLAYER_SPEED*moveState*timeElapsed;
}