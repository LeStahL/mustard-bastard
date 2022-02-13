#include "Enemy.hpp"
#include "Entity.h"
#include "FloorThing.hpp"
#include <GameLogic.h>
#include <Medikit.hpp>

#include <random>
#include <iostream>
#include <algorithm>
#include <const.h>
#include <time.h>

static const EntityType AllEnemyTypes[] = {EntityType::ZombieAndCat, EntityType::IcebergAndFairy};

GameLogic::GameLogic(Model* model) :
        model(model) {
    srand(time(NULL));

    for (int p = 0; p < model->getNumberOfPlayers(); p++) {
        playerLogic.push_back(new PlayerLogic(model->getPlayer(p)));
    }

    for (auto enemyType : AllEnemyTypes) {
        enemySpawnCooldown[enemyType] = INIT_COOLDOWN.at(enemyType).getUniformRandom();
    }
}

void GameLogic::update(float timeElapsed) {
    updateEnemies(timeElapsed);
    updateFloorThings(timeElapsed);

    for (int p = 0; p < nPlayers(); p++)
    {
        playerLogic[p]->update(timeElapsed);
        handlePlayerCollisions(playerLogic[p], timeElapsed);
    }
}

void GameLogic::move_player(int player_number, int x_sign, bool retreat, int z_sign, bool attack) {
    auto pl = playerLogic[player_number];
    if (pl->isLocked()) {
        return;
    }
    pl->move_x(x_sign, retreat);
    pl->move_z(z_sign);
    if (attack) {
        pl->attack();
    }
}

void GameLogic::updateEnemies(float timeElapsed) {

    for (const auto enemyType : AllEnemyTypes) {
        if (enemySpawnCooldown[enemyType] > 0) { // TODO -> Cooldownable
            enemySpawnCooldown[enemyType] -= timeElapsed;
        } else {
            spawnEnemy(enemyType, timeElapsed);
            enemySpawnCooldown[enemyType] = INIT_COOLDOWN.at(enemyType).getUniformRandom();
        }
    }

    for (auto enemy : model->getEnemies()) {
        enemy->doTargetUpdates(model, timeElapsed);
        enemy->doCoordUpdates(timeElapsed);

        if (isEnemyTooFarAway(enemy))
        {
            killEnemy(enemy);
        }
    }
}

void GameLogic::spawnEnemy(EntityType type, float elapsed) {
    float spawn_distance = 100;
    auto position = WorldCoordinates::RandomPositionOutside(spawn_distance);
    Enemy* enemy;
    switch (type) {
        case EntityType::ZombieAndCat:
            enemy = Enemy::getZombie(position);
            break;
        case EntityType::IcebergAndFairy:
            enemy = Enemy::getIceberg(position);
            break;
        default:
            return;
    }
    float far_other_side = position.x < 0 ? 2 * WIDTH : -WIDTH;
    enemy->targetFixedX(far_other_side);
    model->getEnemies().push_back(enemy);
}

bool GameLogic::isEnemyTooFarAway(Enemy* enemy) {
    return fabs(enemy->coords.x - 0.5 * WIDTH) > WIDTH;
}

void GameLogic::killEnemy(Enemy* enemy) {
    for(auto it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
        if((*it)->id == enemy->id) {
            model->getEnemies().erase(it);
            break;
        }
    }
}

int GameLogic::nPlayers() {
    return model->getNumberOfPlayers();
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
    maybeSpawnFloorThing(EntityType::Portal);
    maybeSpawnFloorThing(EntityType::Medikit);

    for (FloorThing* floory : model->getFloorThings()) {
        auto portal = dynamic_cast<Portal*>(floory);
        if (portal != nullptr) {
            if (!updatePortal(portal, elapsedTime)) {
                killPortal(floory);
            };
        }
    }
}

void GameLogic::maybeSpawnFloorThing(EntityType type) {
    bool doSpawn = rand() % FLOOR_THING_SPAWN_MODULO.at(type) < 1;
    if (!doSpawn)
        return;

    float random_x = PLAYER_X_BORDER_MARGIN
        + (float)(rand() % 1000) * 0.001 * (WIDTH - 2 * PLAYER_X_BORDER_MARGIN);
    int random_z = rand() % Z_PLANES;

    switch(type) {
    case EntityType::Portal:
        model->getFloorThings().push_back(new Portal(WorldCoordinates(random_x, random_z, true)));
        break;
    case EntityType::Medikit:
        model->getFloorThings().push_back(new Medikit(WorldCoordinates(random_x, random_z, true)));
        break;
    default:
        break;
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

void GameLogic::handlePlayerCollisions(PlayerLogic *playerLogic, float elapsed)
{
    for (Entity* entity : model->getFloorThings()) {
        if (!playerLogic->canCollide()) {
            return;
        }
        if (!entity->canCollide()) {
            continue;
        }
        playerLogic->handleCollisions(entity, elapsed);
    }
}
