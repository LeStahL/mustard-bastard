#ifndef OBJECT_H
#define OBJECT_H

#include <IsDrawable.hpp>

class Object : public IsDrawable {
    public:
    Object(int graphicId, IsDrawable::DrawType drawType, WorldPosition pos);
    
};

#endif /* OBJECT_H */