#include <Object.h>

Object::Object(int graphicId, IsDrawable::DrawType drawType, WorldPosition pos) : 
        IsDrawable(graphicId, drawType),
        Entity(pos)
{

}