#include <GameLogic.h>
#include <iostream>

GameLogic::GameLogic(Model* model) :
    model(model) {
}

void GameLogic::update(float timeElapsed) {
    for (int p = 0; p < nPlayers(); p++)
    {
        updatePlayer(model->getPlayer(p), timeElapsed);
    }
}

void GameLogic::move_x(int player_number, int sign) {
    auto player = model->getPlayer(player_number);
    bool switch_direction = player->orientation.facing_left && (sign > 0)
        || !player->orientation.facing_left && (sign < 0);

    if (switch_direction) {
        player->x_speed = 0;
        player->orientation.facing_left = !player->orientation.facing_left;
    } else {
        player->x_speed = sign * PLAYER_SPEED;
    }
}

void GameLogic::updatePlayer(Player* player, float timeElapsed) {
    // move model
    player->position.x += player->x_speed * timeElapsed;
}

int GameLogic::nPlayers() {
    return model->getNumberOfPlayers();
}
