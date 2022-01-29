#pragma once

class IsDrawable {
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
    IsDrawable(int graphicId, DrawType drawType);
    int getGraphicId();
    DrawType getDrawType();
    virtual void customDraw(double time) {};
};