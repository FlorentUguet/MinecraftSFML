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

void Scene::newFrame()
{
    this->vpNeedsUpdate = true;
}

glm::mat4 Scene::getVP()
{
    if(this->vpNeedsUpdate)
    {
        this->vpMatrix = this->camera->getProjectionMatrix() * this->camera->getViewMatrix();
        this->vpNeedsUpdate = false;
    }

    return this->vpMatrix;
}

glm::mat4 Scene::calculateMVP(OpenGLEntity *e)
{
    return this->getVP() * e->getTransformedMatrix();
}

void Scene::draw()
{
    this->newFrame();
    this->root->draw(this);
}
