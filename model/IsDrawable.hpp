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

    protected:
    int graphicId;
    DrawType drawType;

    public:
    IsDrawable(int graphicId, DrawType drawType);
    int getGraphicId();
    DrawType getDrawType();
};