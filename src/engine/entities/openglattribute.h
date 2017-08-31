#ifndef OPENGLATTRIBUTE_H
#define OPENGLATTRIBUTE_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "opengl.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../glutils.h"

class OpenGLAttribute
{
public:
    template<typename T>
    OpenGLAttribute(GLuint id, T data[], GLint size, GLenum type, GLboolean normalized, GLsizei stride);

    void setIndex(GLuint id);

    template<typename T>
    void generate(T data[]);

    void bind();
    void enable();
    void disable();

    void setAttribDivisor(GLuint divisor = 0);

    GLuint getBufferId();

private:
    GLuint buffer = 0;
    GLuint index = 0;

    GLint size = 0;
    GLboolean normalized = GL_FALSE;
    GLsizei stride = 0;
    GLuint divisor = 0;
    GLenum type = 0;

    bool hasDivisor = false;
};

#endif // OPENGLATTRIBUTE_H
