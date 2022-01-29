#include <IsDrawable.hpp>

IsDrawable::IsDrawable(int graphicId, DrawType drawType) :
        graphicId(graphicId),
        drawType(drawType),
        x(0.0f),
        y(0.0f) {
}

int IsDrawable::getGraphicId() {
    return graphicId;
}

IsDrawable::DrawType IsDrawable::getDrawType() {
    return drawType;
}