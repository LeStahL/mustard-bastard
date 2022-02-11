#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include <WorldPosition.h>
#include <WorldOrientation.h>

class Entity {
    private:
        static int id_counter;
    protected:
        bool is_locked = false;
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

        virtual std::pair<float, float> getCollisionXInterval();
        virtual bool canCollide();

//        virtual bool onCollisionWith(Entity* other, void (*callback)(Entity* other)) = 0;
};

#endif /* ENTITY_H */