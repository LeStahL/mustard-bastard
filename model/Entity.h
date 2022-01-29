#ifndef ENTITY_H
#define ENTITY_H

#include <WorldPosition.h>
#include <WorldOrientation.h>

class Entity {
    private:
        static int id_counter;
    public:
        int id;
        WorldPosition position;
        WorldOrientation orientation;
        float x_speed = 0;

    public:
        Entity(WorldPosition position, WorldOrientation orientation) :
        id(id_counter++),
        position(position),
        orientation(orientation)
        { }

        Entity(WorldPosition position) : Entity(position, WorldOrientation())
        { }

        virtual ~Entity() {}
        //virtual void OverrideMe() = 0;
};

#endif /* ENTITY_H */