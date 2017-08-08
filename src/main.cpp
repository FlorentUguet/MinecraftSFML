#include <iostream>
#include <SFML/Config.hpp>

#include "controller/renderer.h"
#include "opengl/triangle2d.h"
#include "opengl/plane2d.h"

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

    OpenGLEntity *e = new OpenGLEntity();
    e->show();


    Plane2D *p = new Plane2D(e);
    p->translate(0.f,0.f,1.f);
    p->init();


    Triangle2D *t = new Triangle2D(e);
    t->translate(0.f,0.f,-1.f);
    t->init();

    Tests::TestEntity(r,e);


    return 0;
}
