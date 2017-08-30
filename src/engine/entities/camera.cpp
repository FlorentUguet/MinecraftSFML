#include "camera.h"

#include "openglentity.h"

Camera::Camera(float fov, float ratio, float near, float far, OpenGLEntity* parent) : OpenGLEntity(parent)
{
    setFov(fov);
    setRatio(ratio);
    setNear(near);
    setFar(far);
}

void Camera::init()
{

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(
        this->translation, // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Camera::getProjectionMatrix()
{
    float rad = glm::radians(this->fov);
    return glm::perspective(rad,this->ratio, this->near, this->far);
}

void Camera::setFov(float fov)
{
    this->fov = fov;
}

void Camera::setRatio(float ratio)
{
    this->ratio = ratio;
}

void Camera::setRatio(float w, float h)
{
    setRatio(w/h);
}

void Camera::setNear(float near)
{
    this->near = near;
}

void Camera::setFar(float far)
{
    this->far = far;
}
