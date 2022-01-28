#ifndef WORLD_POSITION_H
#define WORLD_POSITION_H

class WorldPosition {
    public:
        float x;
        int z;
        bool upWorld;

        WorldPosition(float x, int z, bool upWorld);
        void toggleWorld();
};

#endif /* WOLRD_POSITION_H */