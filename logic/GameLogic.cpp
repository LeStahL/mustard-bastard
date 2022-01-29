#include <GameLogic.h>
#include <random>
#include <iostream>

GameLogic::GameLogic(Model& model) :
        model(model),
        moveState(0) {

    srand(1337); // TODO: replace with time
}

void GameLogic::update(float timeElapsed) {
    updatePlayer(timeElapsed);
    updateEnemies(timeElapsed);

    model.getPlayer().x = model.getPlayer().position.x;
}

void GameLogic::updateEnemies(float timeElapsed) {
    // spwan new enemies with probabilty of 5% for 100 calls
    if(rand() % 500 < 1)
        spawnEnemy();

    // move all enemies by their own speed
    for(Enemy* enemy : model.getEnemies()) {
        enemy->position.x -= enemy->speed*timeElapsed;
        enemy->x = enemy->position.x;
    }
}

void GameLogic::spawnEnemy() {
    Enemy* enemy = new Enemy(Model::GraphicsId::zombie, WorldPosition(1000.0f, 0, true));
    model.getEnemies().push_back(enemy);
    model.getGameViewModel().getLayer(1)->push_back(enemy);
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