#ifndef OBJECT_H
#define OBJECT_H

#include <Entity.h>
#include <IsDrawable.hpp>

class Object : public Entity, public IsDrawable {
    public:
    Object(int graphicId, IsDrawable::DrawType drawType, WorldPosition pos);
    
};

#endif /* OBJECT_H */