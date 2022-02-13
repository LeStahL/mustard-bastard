#pragma once

#include <const.h>

class WorldCoordinates {
    public:
        float x;
        float y = 0; // ground
        int z;
        bool upWorld;
        float rotation;
        bool facing_left;

        float x_speed = 0;
        float x_acc = 0;
        float y_speed = 0;
        float y_acc = 0;
        float collision_width = 0;

        WorldCoordinates(float x, int z, bool upWorld);
        void toggleWorld();
        bool collides_with(WorldCoordinates other);

        void doPhysicalUpdates(float deltaT);
        void applyAcceleration(float x_acc, float y_acc, bool stop_first);

        static WorldCoordinates RandomPositionOutside(float distance);

        void mightTurnAroundForTarget(float target_x);
};
