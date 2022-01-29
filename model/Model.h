#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <Entity.h>

class Model {
    private:
    std::vector<Entity> entities;

    public:
    Model();
    std::vector<Entity>& getEntities();
};

#endif /* MODEL_H */