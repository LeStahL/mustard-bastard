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
