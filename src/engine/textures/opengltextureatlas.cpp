#include "opengltextureatlas.h"

OpenGLTextureAtlas::OpenGLTextureAtlas(std::string file, int x, int y)
{
   this->load(file,x,y);
}

void OpenGLTextureAtlas::load(std::string file, int x, int y)
{
    this->texture = new OpenGLTexture(file);

    this->x = x;
    this->y = y;

    this->w = this->texture->getWidth() / x;
    this->h = this->texture->getHeight() / y;
}

std::vector<GLfloat> OpenGLTextureAtlas::convertUVs(std::vector<GLfloat> UVs, std::vector<GLuint> subtextureID)
{
    std::vector<GLfloat> newUVs;

    for(unsigned int i=0;i<UVs.size();i++)
    {
        int x = subtextureID[i/2] % this->x;
        int y = subtextureID[i/2] / this->x;

        float r = 0.0;

        if(i%2 == 0)
        {
            //X
            r = (float(x) + UVs[i]) / float(this->x);
        }
        else
        {
            //Y
            r = (float(y) + (1-UVs[i])) / float(this->y);
            r = 1-r;
        }

        newUVs.push_back(r);

    }

    return newUVs;
}

OpenGLTexture *OpenGLTextureAtlas::getTexture()
{
    return this->texture;
}
