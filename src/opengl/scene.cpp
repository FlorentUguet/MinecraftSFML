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

void Scene::setVertexShader(GLuint shader, std::string projection, std::string view, std::string model)
{
    this->programID = shader;

    this->projectionMatrixLocation = glGetUniformLocation(shader, projection.c_str());
    this->viewMatrixLocation = glGetUniformLocation(shader, view.c_str());
    this->modelMatrixLocation = glGetUniformLocation(shader, model.c_str());
    this->MVPLocation = glGetUniformLocation(this->programID, "MVP");

    this->viewMatrix = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    std::cout << "Scene's matrixs loaded : ";
    std::cout << "M:" << this->modelMatrixLocation << ", V:" << this->viewMatrixLocation << ", P:" << this->projectionMatrixLocation << std::endl;
}

glm::mat4 Scene::calculateMVP(OpenGLEntity *e)
{
    return this->projectionMatrix * this->viewMatrix * e->getTransformedMatrix();
}

void Scene::draw()
{
    /*
    if(this->projectionMatrixLocation != 0)
        glUniformMatrix4fv(this->projectionMatrixLocation, 1, GL_FALSE, &this->projectionMatrix[0][0]); // Envoyer la matrice de projection au shader

    if(this->viewMatrixLocation != 0)
        glUniformMatrix4fv(this->viewMatrixLocation, 1, GL_FALSE, &this->viewMatrix[0][0]);
    */

    this->root->draw(this);

    //std::cout << "Errors : " << GLUtils::GetErrors() << std::endl;
    //exit(0);
}
