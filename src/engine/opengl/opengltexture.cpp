#include "opengltexture.h"

OpenGLTexture::OpenGLTexture(std::string file, int xN, int yN, GLenum pixelType)
{
    if(file != "")
    {
        this->load(file, pixelType);
    }

    this->xN = xN;
    this->yN = yN;
}

GLuint OpenGLTexture::getId()
{
    return this->id;
}
void OpenGLTexture::load(std::string file, GLenum pixelType)
{
    this->file = file;
    this->type = pixelType;
    this->id = LoadTexture(file, pixelType);
}

GLuint OpenGLTexture::LoadTexture(std::string file, GLenum pixelType)
{ 
    bool ok = true;

    SDL_Surface *s = IMG_Load(file.c_str());

    if(s != 0)
    {
        return LoadTexture(s->w, s->h, (unsigned char*)s->pixels, pixelType);
    }
    else
    {
        std::cout << "Error loading texture " << file << " : " << IMG_GetError() << std::endl;
        return 0;
    }
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

    //renvoi de l'identifiant
    return textureID;
}
