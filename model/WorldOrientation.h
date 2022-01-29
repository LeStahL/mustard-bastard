#ifndef WORLD_ORIENTATION_H
#define WORLD_ORIENTATION_H

class WorldOrientation {
    public:
        float rotation ;
        bool facing_left;

        WorldOrientation(float rotation, bool facing_left);

        WorldOrientation() : WorldOrientation(0, false)
        { }

};

#endif /* WORLD_ORIENTATION_H */