#include "triangle2d.h"

Triangle2D::Triangle2D(OpenGLEntity *parent) : OpenGLEntity(parent)
{
}

void Triangle2D::init()
{
    addVertice(-1.0f, -1.0f, 0.0f);
    addVertice(1.0f, -1.0f, 0.0f);
    addVertice(0.0f,  1.0f, 0.0f);

    loadBuffer();
}
