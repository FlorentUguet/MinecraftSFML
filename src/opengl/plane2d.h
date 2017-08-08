#ifndef PLANE2D_H
#define PLANE2D_H

#include "openglentity.h"

class Plane2D : public OpenGLEntity
{
public:
    Plane2D(OpenGLEntity *parent = 0);
    void init();

private:
};

#endif // PLANE2D_H
