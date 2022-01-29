#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Player.h>
#include <Entity.h>

class Model {
    private:
    Player player;
    std::vector<Entity*> entities;

    public:
    Model();
    std::vector<Entity*>& getEntities();
    Player& getPlayer();
};

#endif /* MODEL_H */