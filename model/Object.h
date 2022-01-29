#ifndef OBJECT_H
#define OBJECT_H

#include <Entity.h>
#include <IsDrawable.hpp>

class Object : public Entity, public IsDrawable {
    public:
<<<<<<< HEAD
    Object();

=======
    Object(int graphicId, IsDrawable::DrawType drawType, WorldPosition pos);
    
>>>>>>> eumel walking in front of background
};

#endif /* OBJECT_H */