#include "scene.h"

#include "camera.h"
#include "openglentity.h"

Scene::Scene(Camera *c, OpenGLEntity *e)
{
    setCamera(c);
    setRoot(e);
}

void Scene::setCamera(Camera *c)
{
    this->camera = c;
}

void Scene::setRoot(OpenGLEntity* e)
{
    this->root = e;
}

GLint Scene::getMVPId()
{
    return this->MVPLocation;
}

GLint Scene::getModelViewMatrixId()
{
    return this->modelMatrixLocation;
}

void Scene::setVertexShader(GLuint shader)
{
    this->programID = shader;
    this->MVPLocation = glGetUniformLocation(this->programID, "MVP");
}

glm::mat4 Scene::calculateMVP(OpenGLEntity *e)
{
    return this->camera->getProjectionMatrix() * this->camera->getViewMatrix() * e->getTransformedMatrix();
}

void Scene::draw()
{
    this->root->draw(this);
}
