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

    Tests::TestBlock(r);
    return 0;
}
