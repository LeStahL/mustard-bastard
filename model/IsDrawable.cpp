#include <IsDrawable.hpp>

IsDrawable::IsDrawable(int graphicId, DrawType drawType) :
        graphicId(graphicId),
        drawType(drawType) {
}

int IsDrawable::getGraphicId() {
    return graphicId;
}

IsDrawable::DrawType IsDrawable::getDrawType() {
    return drawType;
}