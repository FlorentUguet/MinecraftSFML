#include "box3d.h"

Box3D::Box3D(int x, int y, int z, OpenGLEntity* parent) : Box3D(parent)
{

}

Box3D::Box3D(OpenGLEntity *parent) : OpenGLEntity(parent)
{
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
            plane->translate(0,1.0,0);
            plane->rotate(90.0f);
            break;
        case Sides::BOTTOM:
            plane->translate(0,-0.5,0);
            plane->rotate(-90.0f);
            break;
        case Sides::LEFT:
            plane->translate(-0.5,0,0);
            plane->rotate(0.f,-90.0f);
            break;
        case Sides::RIGHT:
            plane->translate(0.5,0,0);
            plane->rotate(0.f,90.0f);
            break;
        case Sides::FRONT:
            plane->translate(0,0,1);
            break;
        case Sides::BACK:
            plane->translate(0,0,-1);
            plane->rotate(0.f,180.0f);
            break;

        }

        this->sides[i] = plane;
        this->sides[i]->hide();
    }

    this->sides[Sides::TOP]->show();
    this->sides[Sides::BOTTOM]->show();

    loadBuffer();
}

void Box3D::setTextureSide(int side, OpenGLTexture* tex)
{
    this->sides[side]->setTexture(tex);
}
