#include <GameLogic.h>

#include <random>
#include <iostream>

GameLogic::GameLogic(Model* model, GameViewModel* gameViewModel) :
        model(model), gameViewModel(gameViewModel) {
    srand(1337); // TODO: replace with time
}

void GameLogic::update(float timeElapsed) {
    updateEnemies(timeElapsed);

    for (int p = 0; p < nPlayers(); p++)
    {
        updatePlayer(model->getPlayer(p), timeElapsed);
    }
}

void GameLogic::move_x(int player_number, int sign, bool retreat) {
    auto player = model->getPlayer(player_number);
    bool would_switch_direction = player->orientation.facing_left && (sign > 0)
        || !player->orientation.facing_left && (sign < 0)
        ;

    if (would_switch_direction && !retreat) {
        player->x_speed = 0;
        player->orientation.facing_left = !player->orientation.facing_left;
    } else if (retreat) {
        player->x_speed =-sign * PLAYER_SPEED;
    } else {
        player->x_speed = sign * PLAYER_SPEED;
    }
}

void GameLogic::updateEnemies(float timeElapsed) {
    // spwan new enemies with probabilty of 5% for 100 calls
    if(rand() % 500 < 1)
        spawnEnemy();

    // move all enemies by their own speed
    for(Enemy* enemy : model->getEnemies()) {
        enemy->position.x -= enemy->speed*timeElapsed;
        enemy->x = enemy->position.x;

        if (isEnemyToFarAway(enemy))
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
    model->getEnemies().push_back(enemy);
    gameViewModel->getLayer(1)->push_back(enemy);
}

bool GameLogic::isEnemyToFarAway(Enemy* enemy) {
    return abs(enemy->position.x) > 2000; // TODO Screen width
}

void GameLogic::killEnemy(Enemy *enemy) {
    int id = enemy->id;

    for(auto it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
        if((*it)->id == id) {
            model->getEnemies().erase(it);
            break;
        }
    }

    /*
    for(int i = 0; i < Z_LAYER_COUNT; i++) {
        auto layer = gameViewModel->getLayer(i);

        for(auto it = layer.begin(); it != layer.end(); it++) {
            if((*it)->id == id) {
                layer.erase(it);
                return;
            }
        }
    }
    */
}

void GameLogic::move_z(int player_number, int sign) {

}

void GameLogic::attack(int player_number) {

}

void GameLogic::updatePlayer(Player* player, float timeElapsed) {
    // move model
    player->position.x += player->x_speed * timeElapsed;
}

int GameLogic::nPlayers() {
    return model->getNumberOfPlayers();
}
