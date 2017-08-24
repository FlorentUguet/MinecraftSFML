#include "opengltexture.h"

OpenGLTexture::OpenGLTexture(std::string file)
{
    if(file != "")
    {
        this->load(file);
    }
}

GLuint OpenGLTexture::getId()
{
    return this->id;
}
void OpenGLTexture::load(std::string file)
{
    this->id = LoadTexture(file);
}

GLuint OpenGLTexture::LoadTexture(std::string file)
{ 
    bool ok = true;

    SDL_Surface *s = IMG_Load(file.c_str());

    if(s != 0)
    {
        return LoadTexture(s->w, s->h, (unsigned char*)s->pixels);
    }
    else
    {
        std::cout << "Error loading texture " << file << " : " << IMG_GetError() << std::endl;
        return 0;
    }
}

GLuint OpenGLTexture::LoadTexture(int w, int h, unsigned char *pixels)
{
    GLuint textureID = 0;
    //parametrage de la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //renvoi de l'identifiant
    return textureID;
}
