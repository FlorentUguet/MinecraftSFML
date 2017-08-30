#include "opengltexture.h"

OpenGLTexture::OpenGLTexture(std::string file, GLenum pixelType)
{
    if(file != "")
    {
        this->load(file, pixelType);
    }
}

GLuint OpenGLTexture::getId()
{
    return this->id;
}
void OpenGLTexture::load(std::string file, GLenum pixelType)
{
    this->file = file;
    this->type = pixelType;

    this->surface = IMG_Load(file.c_str());

    if(this->surface != 0)
    {
        this->id = LoadTexture(this->surface->w, this->surface->h, (unsigned char*)this->surface->pixels, pixelType);
    }
    else
    {
        std::cout << "Error loading texture " << file << " : " << IMG_GetError() << std::endl;
    }
}

int OpenGLTexture::getWidth()
{
    return this->getSurface()->w;
}

int OpenGLTexture::getHeight()
{
    return this->getSurface()->h;
}

SDL_Surface *OpenGLTexture::getSurface()
{
    return this->surface;
}

GLuint OpenGLTexture::LoadTexture(int w, int h, unsigned char *pixels, GLenum pixelType)
{
    GLuint textureID = 0;
    //parametrage de la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
        gluBuild2DMipmaps(GL_TEXTURE_2D, pixelType, w, h, pixelType, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    //renvoi de l'identifiant
    return textureID;
}
