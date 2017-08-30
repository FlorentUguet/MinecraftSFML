#ifndef OPENGLTEXTUREATLAS_H
#define OPENGLTEXTUREATLAS_H

#include "opengltexture.h"

#include <vector>

class OpenGLTextureAtlas
{
public:
    OpenGLTextureAtlas(std::string file, int x, int y);
    void load(std::string file, int x, int y);

    std::vector<GLfloat> convertUVs(std::vector<GLfloat> UVs, std::vector<GLuint> subtextureID);
    OpenGLTexture *getTexture();

private:
    int x = 0;
    int y = 0;

    int w = 0;
    int h = 0;

    OpenGLTexture *texture = 0;

};

#endif // OPENGLTEXTUREATLAS_H
