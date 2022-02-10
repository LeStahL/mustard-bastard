#pragma once

#include <WorldPosition.h>
#include <WorldOrientation.h>

enum class EntityType {
    Player,
    ZombieAndCat,
    IcebergAndFairy,
    Portal
};

class Entity {
    private:
        static int id_counter;
    protected:
        EntityType type;

    public:
        int id;
        WorldPosition position;
        WorldOrientation orientation;
        float x_speed = 0;

    public:
        Entity(EntityType type, WorldPosition position, WorldOrientation orientation) :
        type(type),
        id(id_counter++),
        position(position),
        orientation(orientation)
        { }

        Entity(EntityType type, WorldPosition position) : Entity(type, position, WorldOrientation())
        { }

        virtual ~Entity() {}

        //virtual bool onCollisionWith(Entity* other, void (*callback)(Entity* other)) = 0;
        EntityType getType();
};