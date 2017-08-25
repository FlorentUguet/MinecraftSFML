#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "opengl.h"
#include <SDL2/SDL_image.h>

#include <iostream>

class OpenGLTexture
{
public:
    OpenGLTexture(std::string file = "", GLenum pixelType = GL_RGB);
    void load(std::string file, GLenum pixelType = GL_RGB);

    GLuint getId();

    static GLuint LoadTexture(std::string file, GLenum pixelType = GL_RGB);
    static GLuint LoadTexture(int w, int h, unsigned char *pixels, GLenum pixelType = GL_RGB);

private:
    GLuint id = 0;
    std::string file;
    GLenum type;
};

#endif // OPENGLTEXTURE_H
