#ifndef OPENGLENTITY_H
#define OPENGLENTITY_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "opengl.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "opengltexture.h"
#include "glutils.h"

class Scene;
#include "scene.h"

#define VERTICE_SIZE 3
#define TEXTURE_COORD_SIZE 2
#define DEFAULT_SCALE 1.0

class OpenGLEntity
{
public:
    OpenGLEntity(OpenGLEntity* parent = 0);
    ~OpenGLEntity();

    void setParent(OpenGLEntity* parent);

    virtual void draw(Scene *scene);
    virtual void init();
    void loadBuffer();

    void translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void rotate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void scale(float scale = DEFAULT_SCALE);

    glm::mat4 getTransformedMatrix();

    void addVertice(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v);
    void addVertice(GLfloat x, GLfloat y, GLfloat z);
    void addTexCoord(GLfloat u, GLfloat v);

    void setTexture(OpenGLTexture *texture);

    void hide();
    void show();
    void setVisible(bool visible);
    bool isVisible();

protected:
    void addChild(OpenGLEntity *e);
    void removeChild(OpenGLEntity *e);

    OpenGLEntity *parent = 0;
    std::vector<OpenGLEntity*> children;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> textureCoordinates;

    glm::vec3 translation = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scaleVec = glm::vec3(DEFAULT_SCALE);

    GLuint vbo = 0;
    GLuint vao = 0;
    GLuint vboTexture = 0;

    OpenGLTexture *texture = 0;

    int verticesCount = 0;

    bool visible = true;
    bool loaded = false;

private:
};

#endif // OPENGLENTITY_H
