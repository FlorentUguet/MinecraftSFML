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
    OpenGLAttribute(GLuint id, const GLvoid * data, GLsizeiptr length, GLint size, GLenum type, GLboolean normalized, GLsizei stride);
    ~OpenGLAttribute();
    void clearBuffer();

    void setIndex(GLuint id);

    void generate(const GLvoid * data, GLsizeiptr length);

    void attach();
    void enable();
    void disable();

    void setAttribDivisor(GLuint divisor = 0);

    GLuint getBufferId();
    GLuint getIndex();
    GLuint getLength();

private:
    GLuint buffer = 0;
    GLuint index = 0;

    GLint size = 0;
    GLboolean normalized = GL_FALSE;
    GLsizei stride = 0;
    GLuint divisor = 0;
    GLenum type = 0;
    GLsizeiptr length = 0;

    bool hasDivisor = false;
};

#endif // OPENGLATTRIBUTE_H
