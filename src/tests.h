#ifndef TESTS_H
#define TESTS_H

#include "engine/opengl/openglentity.h"
#include "engine/controller/renderer.h"
#include "engine/opengl/glutils.h"

#include "engine/opengl/triangle2d.h"
#include "engine/opengl/plane2d.h"
#include "engine/opengl/box3d.h"

#include <glm/glm.hpp>
#include <chrono>

class Tests
{
public:
    Tests();

    static void MatriceOperationsTiming(int number);
    static void TestBlocks(Renderer *r, std::string texSide, std::string texBottom, std::string texTop);
    static void TestShapes(Renderer *r);
    static void TestTexturePlacement(Renderer *r, std::string file);
    static void TestTexture(Renderer *r, std::string file0, std::string file1);
    static void TestEntity(Renderer *r, OpenGLEntity *e);

    static void TestTextureFileSDL(std::string path);
};

#endif // TESTS_H
