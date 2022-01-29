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

        if(isEnemyToFarAway(enemy))
            killEnemy(enemy);
    }
}

void GameLogic::spawnEnemy() {
    Model::GraphicsId graphicsId;
    switch(rand()%3) {
        case 0:
            graphicsId = Model::GraphicsId::zombie;
            break;
        case 1:
            graphicsId = Model::GraphicsId::iceberg;
            break;
        case 2:
            graphicsId = Model::GraphicsId::cat;
            break;
    }

    Enemy* enemy = new Enemy(graphicsId, WorldPosition(1000.0f, 0, true));
    model.getEnemies().push_back(enemy);
    model.getGameViewModel().getLayer(1)->push_back(enemy);
}

bool GameLogic::isEnemyToFarAway(Enemy* enemy) {
    return abs(enemy->position.x) > 2000; // TODO Screen width
}

void GameLogic::killEnemy(Enemy *enemy) {
    int id = enemy->id;

    for(auto it = model.getEnemies().begin(); it != model.getEnemies().end(); it++) {
        if((*it)->id == id) {
            model.getEnemies().erase(it);
            break;
        }
    }

    for(int i = 0; i < Z_LAYER_COUNT; i++) {
        auto layer = *model.getGameViewModel().getLayer(i);

        for(auto it = layer.begin(); it != layer.end(); it++) {
            if((*it)->id == id) {
                layer.erase(it);
                return;
            }
        }
    }
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