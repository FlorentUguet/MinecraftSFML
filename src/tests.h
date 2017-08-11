#ifndef TESTS_H
#define TESTS_H

#include "opengl/openglentity.h"
#include "controller/renderer.h"
#include "opengl/glutils.h"

#include "opengl/triangle2d.h"
#include "opengl/plane2d.h"
#include "opengl/box3d.h"

#include <glm/glm.hpp>
#include <chrono>

class Tests
{
public:
    Tests();

    static void MatriceOperationsTiming(int number);
    static void TestBlock(Renderer *r);
    static void TestShapes(Renderer *r);
    static void TestEntity(Renderer *r, OpenGLEntity *e);
};

#endif // TESTS_H
