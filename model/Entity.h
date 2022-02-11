#pragma once

#include <utility>
#include <WorldCoordinates.h>

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
        bool is_locked = false;
    public:
        int id;
        WorldCoordinates coords;
        float x_speed = 0;

    public:
        Entity(EntityType type, WorldCoordinates coords) :
        type(type),
        id(id_counter++),
        coords(coords)
        { }

        virtual ~Entity() {}

        //virtual bool onCollisionWith(Entity* other, void (*callback)(Entity* other)) = 0;
        EntityType getType();
        virtual std::pair<float, float> getCollisionXInterval();
        virtual bool canCollide();

        void doPhysicalUpdates(float deltaT);
};
