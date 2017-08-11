#include "scene.h"

Scene::Scene(float fov, float ratio, float near, float far)
{
    setPerspective(fov, ratio, near, far);
}

void Scene::setPerspective(float fov, float ratio, float near, float far)
{
    this->projectionMatrix = glm::perspective(glm::radians(fov),ratio,near,far);
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

    this->viewMatrix = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Scene::calculateMVP(OpenGLEntity *e)
{
    return this->projectionMatrix * this->viewMatrix * e->getTransformedMatrix();
}

void Scene::draw()
{
    glGetError();
    this->root->draw(this);
    glGetError();

    /*
    std::string errors = GLUtils::GetErrors();
    if(!errors.empty()) std::cout << "Errors : " << errors  << std::endl;
    */
}
