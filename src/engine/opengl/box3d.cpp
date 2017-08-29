#include "box3d.h"

Box3D::Box3D(OpenGLEntity *parent) : OpenGLEntity(parent)
{

}

void Box3D::init()
{
    float t = 1.0f;

    for(int i=0;i<Sides::COUNT;i++)
    {
        Plane2D *plane = new Plane2D(this);
        plane->init();

        switch(i)
        {
        case Sides::TOP:
            plane->translate(0,t,0);
            plane->rotate(-90.0f);
            break;
        case Sides::BOTTOM:
            plane->translate(0,-t,0);
            plane->rotate(90.0f);
            break;
        case Sides::LEFT:
            plane->translate(t,0,0);
            plane->rotate(0.f,90.0f);
            break;
        case Sides::RIGHT:
            plane->translate(-t,0,0);
            plane->rotate(0.f,-90.0f);
            break;
        case Sides::FRONT:
            plane->translate(0,0,t);
            break;
        case Sides::BACK:
            plane->translate(0,0,-t);
            plane->rotate(0.f,180.0f);
            break;

        }

        this->sides[i] = plane;
    }

    loadBuffer();
}

bool Box3D::setSideVisible(int side, bool visible)
{
    this->sides[side]->setVisible(visible);
}

void Box3D::setTextureSide(int side, OpenGLTexture* tex)
{
    this->sides[side]->setTexture(tex);
}
