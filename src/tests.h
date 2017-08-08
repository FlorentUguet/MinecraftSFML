#ifndef TESTS_H
#define TESTS_H

#include "opengl/openglentity.h"
#include "controller/renderer.h"
#include "opengl/glutils.h"

#include <glm/glm.hpp>
#include <chrono>

class Tests
{
public:
    Tests();

    static void MatriceOperationsTiming(int number);
    static void TestEntity(Renderer *r, OpenGLEntity *e);
};

#endif // TESTS_H
