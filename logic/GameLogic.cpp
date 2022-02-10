#include <GameLogic.h>

#include <random>
#include <iostream>
#include <algorithm>
#include <const.h>
#include <time.h>

GameLogic::GameLogic(Model* model) :
        model(model) {
    srand(time(NULL));
}

void GameLogic::update(float timeElapsed) {
    updateEnemies(timeElapsed);
    updateFloorThings(timeElapsed);

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

    maybeSpawnEnemy(EnemyType::ZombieAndCat);
    maybeSpawnEnemy(EnemyType::IcebergAndFairy);
    maybeSpawnPortal();

    for(auto it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
        auto enemy = (*it);
        enemy->position.x -= enemy->speed * timeElapsed;

        if (isEnemyTooFarAway(enemy))
        {
            killEnemy(enemy);
        }
    }
}

void GameLogic::maybeSpawnEnemy(EnemyType type) {
    if(!(rand() % 1000 < 1))
        return;

    Enemy* enemy = new Enemy(type, WorldPosition(1000.0f, rand() % 3, true));
    model->getEnemies().push_back(enemy);
}

bool GameLogic::isEnemyTooFarAway(Enemy* enemy) {
    return fabs(enemy->position.x) > 2 * WIDTH;
}

void GameLogic::killEnemy(Enemy* enemy) {
    for(auto it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
        if((*it)->id == enemy->id) {
            model->getEnemies().erase(it);
            break;
        }
    }
}

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

void GameLogic::maybeSpawnPortal()
{
    // for now, there's only type FloorThingType::Portal

    bool doSpawn = rand() % PORTAL_SPAWN_MODULO < 1;
    if (!doSpawn)
        return;

    float random_x = PLAYER_X_BORDER_MARGIN
        + (float)(rand() % 1000) * 0.001 * (WIDTH - 2 * PLAYER_X_BORDER_MARGIN);
    int random_z = rand() % Z_PLANES;

    Portal* portal = new Portal(WorldPosition(random_x, random_z, true));
    portal->size = PORTAL_EPSILON_SIZE;
    model->getFloorThings().push_back(portal);

    // workaround: just add another one in the other world
    portal = new Portal(WorldPosition(random_x, random_z, false));
    portal->size = PORTAL_EPSILON_SIZE;
    model->getFloorThings().push_back(portal);
}

auto updatePortal = [](Portal* portal, float elapsedTime) {
    if (portal->spawning) {
        if (portal->size < 1) {
            portal->size *= PORTAL_GROW_FACTOR;
        } else {
            portal->size = 1.;
            portal->spawning = false;
            portal->lifetime = PORTAL_ACTIVE_SECONDS;
        }
    } else {
        if (portal->lifetime > 0) {
            portal->lifetime = std::max(portal->lifetime - elapsedTime, 0.f);
        } else if (portal->size >= PORTAL_EPSILON_SIZE) {
            portal->size *= PORTAL_WANE_FACTOR;
        } else {
            portal->size = 0;
            return false;
        }
    }
    return true;
};

void GameLogic::updateFloorThings(float elapsedTime)
{
    maybeSpawnPortal();

    for (FloorThing* floory : model->getFloorThings()) {
        auto portal = dynamic_cast<Portal*>(floory);
        if (portal != NULL) {
            if (!updatePortal(portal, elapsedTime)) {
                killPortal(floory);
            };
        }
    }
}

void GameLogic::killPortal(FloorThing* floorThing)
{
    int id = floorThing->id;

    auto modelList = model->getFloorThings();
    for(auto it = modelList.begin(); it != modelList.end(); it++) {
        if((*it)->id == id) {
            modelList.erase(it);
            break;
        }
    }
}