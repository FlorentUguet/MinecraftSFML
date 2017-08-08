#include "box3d.h"

Box3D::Box3D(int x, int y, int z, OpenGLEntity* parent) : Box3D(parent)
{

}

Box3D::Box3D(OpenGLEntity *parent) : OpenGLEntity(parent)
{
    init();
}

void Box3D::init()
{

    loadBuffer();
}
