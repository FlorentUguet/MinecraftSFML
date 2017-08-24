#include "plane2d.h"

Plane2D::Plane2D(OpenGLEntity *parent) : OpenGLEntity(parent)
{
}

void Plane2D::init()
{
    addVertice(-1.0f,-1.0f,0.0f);
    addVertice(1.0f,-1.0f,0.0f);
    addVertice(-1.0f,1.0f,0.0f);

    addTexCoord(0.0f,1.0f);
    addTexCoord(1.0f,1.0f);
    addTexCoord(0.0f,0.0f);

    addVertice(1.0f,1.0f,0.0f);
    addVertice(-1.0f,1.0f,0.0f);
    addVertice(1.0f,-1.0f,0.0f);

    addTexCoord(1.0f,0.0f);
    addTexCoord(0.0f,0.0f);
    addTexCoord(1.0f,1.0f);


    loadBuffer();
}
