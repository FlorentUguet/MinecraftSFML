#include "openglattribute.h"

OpenGLAttribute::OpenGLAttribute(GLuint id, const GLvoid * data, GLsizeiptr length, GLint size, GLenum type, GLboolean normalized, GLsizei stride){
    this->setIndex(id);
    this->generate(data, length);

    this->size = size;
    this->type = type;
    this->normalized = normalized;
    this->stride = stride;
}

OpenGLAttribute::~OpenGLAttribute()
{
    this->clearBuffer();
}

void OpenGLAttribute::clearBuffer()
{
    glDeleteBuffers(1,&this->buffer);
}

void OpenGLAttribute::setIndex(GLuint id)
{
    this->index = id;
}

void OpenGLAttribute::generate(const GLvoid * data, GLsizeiptr length){
    if(this->buffer != 0)
        this->clearBuffer();

    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);

    this->length = length;
}

void OpenGLAttribute::attach()
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

    this->divisor = divisor;
    this->hasDivisor = true;
}

GLuint OpenGLAttribute::getBufferId()
{
    return this->buffer;
}

GLuint OpenGLAttribute::getIndex()
{
    return this->index;
}

GLuint OpenGLAttribute::getLength()
{
    return this->length;
}
