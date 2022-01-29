#include <GameLogic.h>

GameLogic::GameLogic(Model& model) :
        model(model),
        moveState(0) {
}

void GameLogic::update(float timeElapsed) {
    updatePlayer(timeElapsed);

    model.getPlayer().x = model.getPlayer().position.x;
}

void GameLogic::stay() {
    moveState = 0;
}

void GameLogic::moveForward() {
    moveState = 1;
}

void GameLogic::moveBackward() {
    moveState = -1;
}

void GameLogic::updatePlayer(float timeElapsed) {
    model.getPlayer().position.x += PLAYER_SPEED*moveState*timeElapsed;
}