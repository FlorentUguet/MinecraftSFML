#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

class OpenGLTexture
{
public:
    OpenGLTexture(std::string file = "");
    void load(std::string file);

    GLuint getId();
    sf::Image *getImage();

    static GLuint LoadTexture(std::string file);
    static GLuint LoadTexture(sf::Image *image);
    static sf::Image *LoadImage(std::string file, bool *ok);

private:
    GLuint id = 0;
    sf::Image *image;
};

#endif // OPENGLTEXTURE_H
