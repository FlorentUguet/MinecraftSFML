#ifndef TESTS_H
#define TESTS_H

#include "engine/entities/openglentity.h"
#include "engine/controller/renderer.h"
#include "engine/glutils.h"

#include "engine/entities/triangle2d.h"
#include "engine/entities/plane2d.h"
#include "engine/entities/box3d.h"
#include "engine/textures/opengltexture.h"
#include "engine/textures/opengltextureatlas.h"
#include "engine/entities/jsonentity.h"

#include "engine/entities/camera.h"

#include "entities/chunkentity.h"

#include "timer.h"

#include <glm/glm.hpp>
#include <chrono>

class Tests
{
public:
    Tests();

    static void TestBlocks(Renderer *r, std::string texSide, std::string texBottom, std::string texTop);
    static void TestShapes(Renderer *r);
    static void TestTexture(Renderer *r, std::string file0, std::string file1);
    static void TestEntity(Renderer *r, OpenGLEntity *e, Camera *c = 0, int loops = 0, bool measure = false);
    static void TestChunk(Renderer *r, int x, int y, unsigned int seed, std::string texSide, std::string texBottom, std::string texTop);
    static void TestCulling(Renderer *r, std::string texSide, std::string texBottom, std::string texTop, glm::vec3 cameraPos);
    static void TestAtlas(std::string file, int x, int y, std::vector<GLfloat> UVs, std::vector<GLuint> IDs);
    static void TestJsonEntity(Renderer *r, std::string file);
    static void TestInstancing(Renderer *r, std::string texture, int x, int z);
};

#endif // TESTS_H
