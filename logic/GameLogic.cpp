#include "Enemy.hpp"
#include "Entity.h"
#include "FloorThing.hpp"
#include <GameLogic.h>
#include <Portal.hpp>
#include <Medikit.hpp>
#include <Weapon.hpp>

#include <random>
#include <iostream>
#include <algorithm>
#include <const.h>
#include <time.h>

static const EntityType AllEnemyTypes[] = {EntityType::ZombieAndCat, EntityType::IcebergAndFairy};

GameLogic::GameLogic(Model* model) :
        model(model) {
    srand(time(NULL));

    for (auto enemyType : AllEnemyTypes) {
        enemySpawnCooldown[enemyType] = INIT_COOLDOWN.at(enemyType).getUniformRandom();
    }
}

void GameLogic::init()
{
    for(PlayerLogic *playerLogic : playerLogic) {
        delete playerLogic;
    }
    playerLogic.clear();

    for (int p = 0; p < model->getNumberOfPlayers(); p++) {
        playerLogic.push_back(new PlayerLogic(model->getPlayer(p)));
    }
}

void GameLogic::update(float timeElapsed) {
    if(model->getGameState() == Model::GameState::Paused)
        return;

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

void GameLogic::pauseGame() {
    model->setGameState(Model::GameState::Paused);
}

void GameLogic::resumeGame() {
    model->setGameState(Model::GameState::Running);
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

    std::vector<FloorThing*> &modelList = model->getFloorThings();
    for (auto it = modelList.begin(); it != modelList.end();) {
        FloorThing *floory = *it;

        Portal *portal = dynamic_cast<Portal*>(floory);
        if (portal != nullptr) {
            if (!updatePortal(portal, elapsedTime)) {
                it = modelList.erase(it);
                continue;
            }
        }

        Medikit *medikit = dynamic_cast<Medikit*>(floory);
        if (medikit != nullptr) {
            if (medikit->wasUsed) {
                it = modelList.erase(it);
                continue;
            } else {
                updateMedikit(medikit, elapsedTime);
            }
        }

        it++;
    }
}

void GameLogic::maybeSpawnFloorThing(EntityType type) {
    bool doSpawn = rand() % FLOOR_THING_SPAWN_MODULO.at(type) < 1;
    if (!doSpawn)
        return;

    float random_x = PLAYER_X_BORDER_MARGIN
        + (float)(rand() % 1000) * 0.001 * (WIDTH - 2 * PLAYER_X_BORDER_MARGIN);
    int random_z = rand() % Z_PLANES;

    WorldCoordinates coords(random_x, random_z, true);

    switch(type) {
    case EntityType::Portal:
        model->getFloorThings().push_back(new Portal(coords));
        break;
    case EntityType::Medikit:
        coords.x_speed = MEDIKIT_INITIAL_X_SPEED_PX_PER_S;
        coords.y = HEIGHT*0.5 + MEDIKIT_SPAWN_HEIGHT_OFFSET;
        coords.y_speed = MEDIKIT_FALL_SPEED_PX_PER_S;
        model->getFloorThings().push_back(new Medikit(coords));
        break;
    default:
        break;
    }
}

void GameLogic::updateMedikit(Medikit *medikit, float elapsedTime) {
    if(!medikit->spawning)
        return;

    medikit->coords.x_acc = -MEDIKIT_X_FREQUENCY_PER_S*(medikit->coords.x-medikit->x0);
    medikit->doCoordUpdates(elapsedTime);
    medikit->spawning = medikit->coords.y > 1e-3f;
}

void GameLogic::handlePlayerCollisions(PlayerLogic *playerLogic, float elapsed)
{
    if (!playerLogic->canCollide()) {
        return;
    }

    auto handleCollision = [=](Entity* entity) {
        if (!entity->canCollide()) {
            return;
        }
        playerLogic->handleCollisions(entity, elapsed);
    };

    for (Entity* entity : model->getFloorThings()) {
        handleCollision(entity);
    }

    for (Entity* entity : model->getEnemies()) {
        handleCollision(entity);
    }
}
