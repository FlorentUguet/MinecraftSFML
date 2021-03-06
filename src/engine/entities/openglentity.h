#ifndef OPENGLENTITY_H
#define OPENGLENTITY_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "opengl.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../glutils.h"

class OpenGLAttribute;
class OpenGLTextureAtlas;
class OpenGLTexture;
class Scene;

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
    void updateVAO();

    void setInstances(std::vector<glm::vec3> instances);

    void translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void translate(glm::vec3 pos);
    void rotate(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void scale(float scale = DEFAULT_SCALE);

    glm::mat4 getTransformedMatrix();
    glm::mat4 getMVP(Scene *scene);

    void addVertice(GLfloat x, GLfloat y, GLfloat z, GLfloat u, GLfloat v);
    void addVertice(GLfloat x, GLfloat y, GLfloat z);
    void addIndice(GLuint i);
    void addTexCoord(GLfloat u, GLfloat v);

    void updateDirectionCulling(OpenGLEntity *reference);

    void setTextureAtlas(OpenGLTextureAtlas *atlas);
    void setTexture(OpenGLTexture *texture);

    void hide();
    void show();
    void setVisible(bool visible);
    bool isVisible();

    GLuint getVAO();
    GLuint getVBOIndices();
    OpenGLTexture *getTexture();

    int getVerticesIndexesCount();

    void clearBuffers();

    OpenGLAttribute *getAttribute(GLuint index);

protected:
    void addChild(OpenGLEntity *e);
    void removeChild(OpenGLEntity *e);

    OpenGLEntity *parent = 0;
    std::vector<OpenGLEntity*> children;

    std::vector<GLfloat> verticesXYZ;
    std::vector<GLfloat> verticesUV;
    std::vector<GLuint> verticesI;
    std::vector<glm::vec3> instances;

    glm::vec3 translation = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scaleVec = glm::vec3(DEFAULT_SCALE);

    GLuint vao = 0;

    std::vector<OpenGLAttribute*> attributes;

    GLuint vboIndices = 0;

    OpenGLTexture *texture = 0;
    OpenGLTextureAtlas *atlas = 0;

    int verticesCount = 0;

    bool visible = true;
    bool loaded = false;

private:
};

#endif // OPENGLENTITY_H
