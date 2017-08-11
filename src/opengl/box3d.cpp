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
    for(int i=0;i<Sides::COUNT;i++)
    {
        Plane2D *plane = new Plane2D(this);
        plane->init();

        switch(i)
        {
        case Sides::TOP:
            plane->translate(0,0.5,0);
            plane->rotate(90.0f);
            break;
        case Sides::BOTTOM:
            plane->translate(0,-0.5,0);
            break;
        case Sides::LEFT:
            plane->translate(-0.5,0,0);
            break;
        case Sides::RIGHT:
            plane->translate(0.5,0,0);
            break;
        case Sides::FRONT:
            plane->translate(0,0,0);
            break;
        case Sides::BACK:
            plane->translate(0,0,-1.0);
            break;
        }
    }

    loadBuffer();
}
