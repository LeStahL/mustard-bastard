#ifndef ENTITY_H
#define ENTITY_H

#include <WorldPosition.h>

class Entity {
    private:
        static int id_counter;
    public:
        int id;
        WorldPosition position;

    public:
        Entity(WorldPosition position) :
        id(id_counter++),
        position(position) {

        }
        virtual ~Entity() {}
        //virtual void OverrideMe() = 0;
};

#endif /* ENTITY_H */