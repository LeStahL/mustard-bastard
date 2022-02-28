#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Enemy.hpp>
#include <FloorThing.hpp>

class Model {
    public:
    enum GraphicsId {
        player_standing,
        player_walking,
        player_attack,
        zombie,
        cat,
        iceberg,
        fairy,
        medikit,
        parachute
    };

    enum class GameState {
        Running,
        Paused
    };

    private:
    std::vector<Player*> players;
    std::vector<Enemy*> enemies;
    std::vector<FloorThing*> floorThings;

    GameState gameState;

    public:
    Model();
    void reset();

    void setGameState(const GameState newGameState);
    GameState getGameState() const;

    Player* getPlayer(int player_number);
    int getNumberOfPlayers();
    std::vector<Enemy*>& getEnemies();
    std::vector<FloorThing*>& getFloorThings();
};

#endif /* MODEL_H */
