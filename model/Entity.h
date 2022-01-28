#ifndef ENTITY_H
#define ENTITY_H

#include <WorldPosition.h>

class Entity {
    protected:
        int id;
        WorldPosition position;

    public:
        Entity(int id, WorldPosition position) :
        id(id),
        position(position) {

        }
        virtual ~Entity() {}
        //virtual void OverrideMe() = 0;
};

#endif /* ENTITY_H */