#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <map>
#include <Model.h>
#include <GameViewModel.hpp>
#include <AttackState.hpp>
#include <FloorThing.hpp>

constexpr float PLAYER_MOVE_X_SPEED = 160.0;
constexpr float PLAYER_MOVE_Z_COOLDONW = 0.3;
constexpr float PLAYER_X_BORDER_MARGIN = 30.;
constexpr float PLAYER_MAX_ACCEPTABLE_MUSTARDNESS = 30;
constexpr float PLAYER_MUSTARDNESS_PER_SPOON = 13;
constexpr float PLAYER_MUSTARDNESS_REDUCTION_FACTOR = 0.5;
constexpr float PLAYER_ATTACK_POWER_REDUCTION_FACTOR = 0.8;
constexpr float PLAYER_ATTACK_POWER_RECREATION = 0.008;
constexpr float PLAYER_ATTACK_POWER_FAIRY_RECREATION = 0.1;
constexpr float PLAYER_MIN_REQUIRED_POWER = 0.3;

constexpr int PORTAL_SPAWN_MODULO = 2000;
constexpr float PORTAL_EPSILON_SIZE = 0.001;
constexpr float PORTAL_GROW_FACTOR = 1.01;
constexpr float PORTAL_WANE_FACTOR = 0.996;
constexpr float PORTAL_ACTIVE_SECONDS = 4;
constexpr float PORTAL_MAX_HALFWIDTH = 42;
constexpr float PORTAL_HEIGHT_RATIO = 0.3;

class GameLogic {
    private:
    Model* model;
    GameViewModel* gameViewModel;

    const std::map<Weapon, double> ATTACK_COOLDOWN = {
        {Weapon::Hand, 500.},
        {Weapon::Axe, 2000.},
        {Weapon::Mustard, 1000.},
    };

    public:
    GameLogic(Model* model, GameViewModel* gameViewModel);
    void update(float elapsedTime);
    void move_x(int player, int sign, bool retreat);
    void move_z(int player, int sign);
    void attack(int player);
    int nPlayers();

    private:
    void updatePlayer(Player* player, float elapsedTime);
    void updateEnemies(float elapsedTime);
    void maybeSpawnEnemy(EnemyType type);
    bool isEnemyToFarAway(Enemy* enemy);
    void killEnemy(Enemy* enemy);
    void maybeSpawnFloorThing(FloorThingType type);
    void updateFloorThings(float elapsedTime);
    void killFloorThing(FloorThing* floorThing);
};

#endif /* GAMELOGIC_H */

