#ifndef BOX3D_H
#define BOX3D_H

#include "openglentity.h"
#include "plane2d.h"

class Box3D : public OpenGLEntity
{
public:
    Box3D(int x, int y, int z, OpenGLEntity* parent = nullptr);
    Box3D(OpenGLEntity* parent = nullptr);
    void init();
    void setTextureSide(int side, OpenGLTexture *tex);
    bool setSideVisible(int side, bool visible);

    enum Sides{
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        COUNT
    };

private:
    OpenGLEntity *sides[(int)Sides::COUNT];
};

#endif // BOX3D_H
