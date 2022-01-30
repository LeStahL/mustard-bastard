#include <GameLogic.h>

#include <random>
#include <iostream>
#include <algorithm>
#include <const.h>

GameLogic::GameLogic(Model* model) :
        model(model) {
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
        || !player->orientation.facing_left && (sign < 0);

    if (would_switch_direction && !retreat) {
        player->x_speed = 0;
        player->orientation.facing_left = !player->orientation.facing_left;
    } else if (retreat) {
        player->x_speed = -sign * PLAYER_MOVE_X_SPEED;
    } else {
        player->x_speed = sign * PLAYER_MOVE_X_SPEED;
    }

    player->state = player->x_speed == 0 ? PlayerState::Standing : PlayerState::Walking;
}

void GameLogic::move_z(int player_number, int sign) {
    if (sign == 0)
        return;

    auto player = model->getPlayer(player_number);

    if (player->move_z_cooldown <= 0) {
        player->position.z = std::clamp(player->position.z + sign, 0, (int)Z_PLANES - 1);
        player->move_z_cooldown = PLAYER_MOVE_Z_COOLDONW;
    }
}

void GameLogic::attack(int player_number) {
    auto player = model->getPlayer(player_number);
    bool canAttack = player->attack_state.cooldown <= 0
        && player->attack_state.mustardedness <= PLAYER_MAX_ACCEPTABLE_MUSTARDNESS
        && player->power >= PLAYER_MIN_REQUIRED_POWER;

    if (canAttack) {
        player->state = PlayerState::Attacking;
        player->attack_state.setCoolDown(ATTACK_COOLDOWN.at(player->attack_state.weapon));
        player->power *= PLAYER_ATTACK_POWER_REDUCTION_FACTOR;
    }
}

void GameLogic::updateEnemies(float timeElapsed) {
    // spwan new enemies with probabilty of 5% for 100 calls

    //maybeSpawnEnemy(EnemyType::ZombieAndCat);
    //maybeSpawnEnemy(EnemyType::IcebergAndFairy);
    maybeSpawnFloorThing(FloorThingType::Portal);

    std::cout << model->getEnemies().size() << std::endl;

    // move all enemies by their own speed
    for(Enemy enemy : model->getEnemies()) {
        enemy.position.x -= enemy.speed*timeElapsed;
        

        //std::cout << "move " << enemy.position.x << std::endl;
        //if (isEnemyToFarAway(enemy)) {
        //    killEnemy(enemy);
        //}
    }
}

void GameLogic::maybeSpawnEnemy(EnemyType type) {
    if(!(rand() % 100 < 1) && model->getEnemies().size() < 1)
        return;

    Enemy enemy(type, WorldPosition(1000.0f, 2, true));
    model->getEnemies().push_back(enemy);
}

bool GameLogic::isEnemyToFarAway(Enemy* enemy) {
    return abs(enemy->position.x) > 2000; // TODO Screen width
}

/*void GameLogic::killEnemy(Enemy *enemy) {
    int id = enemy->id;

    for(auto it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
        if((*it)->id == id) {
            model->getEnemies().erase(it);
            break;
        }
    }
}*/

void GameLogic::updatePlayer(Player* player, float timeElapsed) {
    player->position.x = std::clamp(
        player->position.x + player->x_speed * timeElapsed,
        PLAYER_X_BORDER_MARGIN,
        WIDTH - PLAYER_X_BORDER_MARGIN
    );
    player->move_z_cooldown = std::max(player->move_z_cooldown - timeElapsed, 0.f);
    player->attack_state.coolDown(timeElapsed);
}

int GameLogic::nPlayers() {
    return model->getNumberOfPlayers();
}

void GameLogic::maybeSpawnFloorThing(FloorThingType type)
{

}

void GameLogic::updateFloorThings(float elapsedTime)
{

}

void GameLogic::killFloorThing(FloorThing* floorThing)
{

}