#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include "opengl.h"
#include <SDL2/SDL_image.h>

#include <iostream>

class OpenGLTexture
{
public:
    OpenGLTexture(std::string file = "");
    void load(std::string file);

    GLuint getId();

    static GLuint LoadTexture(std::string file);
    static GLuint LoadTexture(int w, int h, unsigned char *pixels);

private:
    GLuint id = 0;
};

#endif // OPENGLTEXTURE_H
