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

    static GLuint LoadTexture(int w, int h, unsigned char *pixels, GLenum pixelType = GL_RGB);

    int getWidth();
    int getHeight();
    SDL_Surface *getSurface();

private:
    GLuint id = 0;
    std::string file;
    GLenum type;

    SDL_Surface *surface = 0;

    int xN;
    int yN;
};

#endif // OPENGLTEXTURE_H
