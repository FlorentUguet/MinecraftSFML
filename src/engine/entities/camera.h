#ifndef CAMERA_H
#define CAMERA_H

#include "opengl.h"

class OpenGLEntity;
#include "openglentity.h"

#include <glm/glm.hpp>

#define CAMERA_RATIO (4.0f/3.0f)
#define CAMERA_FOV 60.0f
#define CAMERA_NEAR 1.0f
#define CAMERA_FAR 100.0f

class Camera : public OpenGLEntity
{
public:
    Camera(float fov = CAMERA_FOV, float ratio = CAMERA_RATIO, float near = CAMERA_NEAR, float far = CAMERA_FAR, OpenGLEntity* parent = nullptr);
    void init();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setFov(float fov);
    void setRatio(float ratio);
    void setRatio(float w, float h);
    void setNear(float near);
    void setFar(float far);
private:

    float fov = CAMERA_FOV;
    float ratio = CAMERA_RATIO;
    float near = CAMERA_NEAR;
    float far = CAMERA_FAR;

};

#endif // CAMERA_H
