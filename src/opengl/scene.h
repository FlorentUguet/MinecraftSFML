#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>

#include <vector>

class OpenGLEntity;
#include "openglentity.h"

#define SCENE_RATIO (4.0f/3.0f)
#define SCENE_FOV 60.0f
#define SCENE_NEAR 1.0f
#define SCENE_FAR 100.0f

class Scene
{
public:
    Scene(float fov = SCENE_FOV, float ratio = SCENE_RATIO, float near = SCENE_NEAR, float far = SCENE_FAR);
    void setRoot(OpenGLEntity* e);

    void setVertexShader(GLuint shader);

    GLint getMVPId();
    GLint getModelViewMatrixId();

    void setPerspective(float fov = SCENE_FOV, float ratio = SCENE_RATIO, float near = SCENE_NEAR, float far = SCENE_FAR);

    glm::mat4 calculateMVP(OpenGLEntity *e);
    void draw();

private:
    OpenGLEntity* root;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    GLint projectionMatrixLocation = 0;
    GLint viewMatrixLocation = 0;
    GLint modelMatrixLocation = 0;
    GLint MVPLocation = 0;

    GLuint programID = 0;

};

#endif // SCENE_H
