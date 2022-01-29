#pragma once

#include <Entity.h>

class IsDrawable : public Entity { // each drawable item is also an entity
    public:
    enum class DrawType {
        texture,
        animation,
        primitive
    };

    float x;
    float y;
    bool facing_left;

    protected:
    int graphicId;
    DrawType drawType;

    public:
    IsDrawable(int graphicId, DrawType drawType, WorldPosition position, WorldOrientation orientation);
    IsDrawable(int graphicId, DrawType drawType, WorldPosition position)
        : IsDrawable(graphicId, drawType, position, WorldOrientation()) {}

    int getGraphicId();
    DrawType getDrawType();
    virtual void customDraw(double time) {};
};