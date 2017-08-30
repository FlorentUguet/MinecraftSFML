#include "box3d.h"

Box3D::Box3D(OpenGLEntity *parent) : OpenGLEntity(parent)
{
    for(int i=0;i<Sides::COUNT;i++)
    {
        this->sides[i] = 0;
    }
}

void Box3D::init()
{
    this->addVertice(-1,-1,1);
    this->addVertice(1,-1,1);
    this->addVertice(1,1,1);
    this->addVertice(-1,1,1);

    this->addVertice(-1,-1,-1);
    this->addVertice(-1,-1,1);
    this->addVertice(-1,1,1);
    this->addVertice(-1,1,-1);

    this->addVertice(1,-1,-1);
    this->addVertice(-1,-1,-1);
    this->addVertice(-1,1,-1);
    this->addVertice(1,1,-1);

    this->addVertice(1,-1,1);
    this->addVertice(1,-1,1);
    this->addVertice(1,1,-1);
    this->addVertice(1,1,1);

    this->addVertice(-1,1,1);
    this->addVertice(1,1,1);
    this->addVertice(1,1,-1);
    this->addVertice(-1,1,-1);

    this->addVertice(-1,-1,-1);
    this->addVertice(1,-1,-1);
    this->addVertice(1,-1,1);
    this->addVertice(-1,-1,1);

    for(int i=0;i<6;i++)
    {
        this->addTexCoord(0,0);
        this->addTexCoord(1,0);
        this->addTexCoord(1,1);
        this->addTexCoord(0,1);
    }

    std::vector<GLuint> indices = {
        0,1,2,0,2,3,
        4,5,6,4,6,7,
        8,9,10,8,10,11,
        12,13,14,12,14,15,
        16,17,18,16,18,19,
        20,21,22,20,22,23
    };

    this->verticesI = indices;

    loadBuffer();
}

bool Box3D::setSideVisible(int side, bool visible)
{
    this->sides[side]->setVisible(visible);
}

void Box3D::setTextureSide(int side, OpenGLTexture* tex)
{
    if(this->sides[side] != 0)
        this->sides[side]->setTexture(tex);
}
