#include <iostream>
#include <SFML/Config.hpp>

#include "controller/renderer.h"

#include "tests.h"

int main()
{
    std::cout << "SFML Version : " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;

    //Tests::MatriceOperationsTiming(10000);


    Renderer *r = new Renderer(800,600,"Renderer");
    r->setVerticalSyncEnabled(true);
    glewInit();

    sf::ContextSettings settings = r->getSettings();
    //OpenGL version
    std::cout << "OpenGL Version : " << settings.majorVersion << "." << settings.minorVersion << std::endl;

    //Tests::TestTexture(r, "textures/dirt.jpg", "textures/stone.jpg");
    Tests::TestBlock(r,"textures/dirt-side.jpg","textures/dirt.jpg","textures/grass.jpg");
    //Tests::TestTexturePlacement(r,"textures/dirt-side.jpg");

    return 0;
}
