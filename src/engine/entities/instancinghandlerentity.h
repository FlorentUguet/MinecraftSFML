#ifndef INSTANCINGHANDLERENTITY_H
#define INSTANCINGHANDLERENTITY_H

#define MAX_INSTANCE_RENDERING 1024

#include "openglentity.h"
#include <sstream>

class InstancingHandlerEntity : public OpenGLEntity
{
public:
    InstancingHandlerEntity(OpenGLEntity *parent = 0);
    void setSource(OpenGLEntity *e);

    void setOffsets(std::vector<glm::vec3> offsets);

    void setShader(GLuint vertexShader);

    void draw(Scene *scene);

private:
    OpenGLEntity *source;
    std::vector<glm::vec3> offsets;
    std::vector<glm::vec2> UVs;

    GLuint shader = 0;
    GLuint vboOffsets = 0;
};

#endif // INSTANCINGHANDLERENTITY_H
