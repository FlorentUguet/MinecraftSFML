#include "opengltexture.h"

OpenGLTexture::OpenGLTexture(std::string file)
{
    if(file != "")
    {
        this->load(file);
    }
}

void OpenGLTexture::load(std::string file)
{
    bool ok = true;

    this->image = OpenGLTexture::LoadImage(file,&ok);

    if(ok)
    {
        this->id = LoadTexture(image);
    }
    else
    {
        std::cout << "Error loading texture " << file << std::endl;
    }
}

GLuint OpenGLTexture::getId()
{
    return this->id;
}

sf::Image *OpenGLTexture::getImage()
{
    return this->image;
}

GLuint OpenGLTexture::LoadTexture(std::string file)
{
    bool ok = true;

    sf::Image* image = LoadImage(file,&ok);

    if(ok)
    {
        return LoadTexture(image);
    }
    else
    {
        std::cout << "Error loading texture " << file << std::endl;
        return 0;
    }
}

GLuint OpenGLTexture::LoadTexture(sf::Image *image)
{
    GLuint textureID = 0;
    //parametrage de la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image->getSize().x, image->getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //renvoi de l'identifiant
    return textureID;
}

sf::Image *OpenGLTexture::LoadImage(std::string file, bool *ok)
{
    //chargement de l'image dont le nom de fichier est reçu en paramètre
    sf::Image *Image = new sf::Image();
    *ok = Image->loadFromFile(file);
    return Image;
}
