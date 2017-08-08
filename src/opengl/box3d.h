#ifndef BOX3D_H
#define BOX3D_H

#include "openglentity.h"

class Box3D : public OpenGLEntity
{
public:
    Box3D(int x, int y, int z, OpenGLEntity* parent = nullptr);
    Box3D(OpenGLEntity* parent = nullptr);
    void init();

private:
};

#endif // BOX3D_H
