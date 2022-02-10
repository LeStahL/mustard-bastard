#ifndef WORLD_POSITION_H
#define WORLD_POSITION_H

class WorldPosition {
    public:
        float x;
        int z;
        bool upWorld;

        float collision_width = 0;

        WorldPosition(float x, int z, bool upWorld);
        void toggleWorld();
        bool collides_with(WorldPosition other);
};

#endif /* WORLD_POSITION_H */