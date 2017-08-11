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
    static void TestBlock(Renderer *r, std::string texSide, std::string texBottom, std::string texTop);
    static void TestShapes(Renderer *r);
    static void TestTexture(Renderer *r, std::string file0, std::string file1);
    static void TestEntity(Renderer *r, OpenGLEntity *e);
};

#endif // TESTS_H
