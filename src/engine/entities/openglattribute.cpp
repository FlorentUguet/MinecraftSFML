#include "openglattribute.h"

template<typename T>
OpenGLAttribute::OpenGLAttribute(GLuint  id, T data[], GLint size, GLenum type, GLboolean normalized, GLsizei stride)
{
    this->setIndex(id);
    this->generate(data);

    this->size = size;
    this->type = type;
    this->normalized = normalized;
    this->stride = stride;
}

void OpenGLAttribute::setIndex(GLuint id)
{
    this->index = id;
}

template<class T>
void OpenGLAttribute::generate(T data[])
{
    if(this->buffer != 0)
        glDeleteBuffers(1,&this->buffer);

    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void OpenGLAttribute::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
        //Vertices
        glVertexAttribPointer(this->index, this->size, this->type, this->normalized, this->stride, (void*)0);
        glEnableVertexAttribArray(this->index);

        if(this->hasDivisor)
            glVertexAttribDivisor(this->index,this->divisor);
}
void OpenGLAttribute::enable()
{
    glEnableVertexAttribArray(this->index);
}

void OpenGLAttribute::disable()
{
    glDisableVertexAttribArray(this->index);
}

void OpenGLAttribute::setAttribDivisor(GLuint divisor)
{
    if(divisor == 0)
        this->hasDivisor = false;

    this->divisor = 0;
}

GLuint OpenGLAttribute::getBufferId()
{
    return this->buffer;
}
