#ifndef SCENE_H
#define SCENE_H

#include "opengl.h"
#include <glm/glm.hpp>
#include <vector>

class Camera;
class OpenGLEntity;

class Scene
{
public:
    Scene(Camera *c = 0, OpenGLEntity *e = 0);
    void setCamera(Camera *c);
    void setRoot(OpenGLEntity* e);

    void setVertexShader(GLuint shader);

    GLint getMVPId();
    GLint getModelViewMatrixId();

    glm::mat4 getVP();
    glm::mat4 calculateMVP(OpenGLEntity *e);
    void draw();

    void newFrame();

private:
    OpenGLEntity* root = 0;
    Camera *camera = 0;

    glm::mat4 vpMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    GLint projectionMatrixLocation = 0;
    GLint viewMatrixLocation = 0;
    GLint modelMatrixLocation = 0;
    GLint MVPLocation = 0;

    GLuint programID = 0;

    bool vpNeedsUpdate = true;

};

#endif // SCENE_H
