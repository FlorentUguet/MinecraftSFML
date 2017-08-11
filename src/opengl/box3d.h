#ifndef BOX3D_H
#define BOX3D_H

#include "openglentity.h"
#include "plane2d.h"

enum Sides{
    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    COUNT
};

class Box3D : public OpenGLEntity
{
public:
    Box3D(int x, int y, int z, OpenGLEntity* parent = nullptr);
    Box3D(OpenGLEntity* parent = nullptr);
    void init();

private:
};

#endif // BOX3D_H
