#include <GameLogic.h>

#include <random>
#include <iostream>
#include <algorithm>
#include <const.h>
#include <time.h>

static const EnemyType AllEnemyTypes[] = {EnemyType::ZombieAndCat, EnemyType::IcebergAndFairy};

GameLogic::GameLogic(Model* model) :
        model(model) {
    srand(time(NULL));

    for (int p = 0; p < model->getNumberOfPlayers(); p++) {
        playerLogic.push_back(new PlayerLogic(model->getPlayer(p)));
    }

    for (auto enemyType : AllEnemyTypes) {
        enemySpawnCooldown[enemyType] = INIT_COOLDOWN.at(enemyType).getUniformRandom();
        std::cout << "SPAWN " << enemyType << " in "  << enemySpawnCooldown[enemyType] << std::endl;
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

    maybeSpawnPortal();

    for (const auto enemyType : AllEnemyTypes) {
        if (enemySpawnCooldown[enemyType] > 0) { // TODO -> Cooldownable
            enemySpawnCooldown[enemyType] -= timeElapsed;
        } else {
            spawnEnemy(enemyType, timeElapsed);
            enemySpawnCooldown[enemyType] = INIT_COOLDOWN.at(enemyType).getUniformRandom();
            std::cout << "SPAWN " << enemyType << " in "  << enemySpawnCooldown[enemyType] << std::endl;
        }
    }

    for (auto enemy : model->getEnemies()) {
        enemy->position.x -= enemy->speed * timeElapsed;

        if (isEnemyTooFarAway(enemy))
        {
            killEnemy(enemy);
        }
    }
}

void GameLogic::spawnEnemy(EnemyType type, float elapsed) {
    bool upWorld = rand() % 2 == 0;
    Enemy* enemy = new Enemy(type, WorldPosition(1000.0f, rand() % 3, upWorld));
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
        if (portal != nullptr) {
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
