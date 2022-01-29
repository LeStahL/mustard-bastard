#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>

class Model {
    public:
    enum class MenuTextureId {
        background
    };
    enum class MenuSpriteId {
    };
    enum class GameTextureId {
        background
    };
    enum class GameSpriteId {
    };

    private:
    Player player;
    std::vector<Entity*> entities;

    public:
    Model();
    std::vector<Entity*>& getEntities();
    Player& getPlayer();
};

#endif /* MODEL_H */