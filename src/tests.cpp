#include "tests.h"

Tests::Tests()
{

}

void Tests::MatriceOperationsTiming(int number)
{
    auto started = std::chrono::high_resolution_clock::now();

    for(int i=0;i<number;i++)
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f)); // On crée la matrice de vue avec une translation en arrière de cinq unités

    auto done = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(done-started).count() << "us for " << number << " operations" << std::endl;
}

void Tests::TestTexture(Renderer *r, std::string file0, std::string file1)
{
    OpenGLEntity *e = new OpenGLEntity();
    e->show();

    OpenGLTexture *texture0 = new OpenGLTexture(file0);
    OpenGLTexture *texture1 = new OpenGLTexture(file1);

    Triangle2D *t0 = new Triangle2D(e);
    t0->translate(0.f,0.f,1.f);
    t0->rotate(0.0f,-135.0f,0.0f);
    t0->setTexture(texture0);
    t0->init();


    Triangle2D *t1 = new Triangle2D(e);
    t1->translate(0.f,0.f,-1.f);
    t1->rotate(0.0f,-90.0f,0.0f);
    t1->setTexture(texture1);
    t1->init();


    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    TestEntity(r,e);
}

void Tests::TestBlock(Renderer *r, std::string texSide, std::string texBottom, std::string texTop)
{
    OpenGLEntity *e = new OpenGLEntity();
    e->show();

    OpenGLTexture *textureTop = new OpenGLTexture(texTop);
    OpenGLTexture *textureBottom = new OpenGLTexture(texBottom);
    OpenGLTexture *textureSide = new OpenGLTexture(texSide);

    Box3D *b = new Box3D(e);
    b->init();

    b->setTextureSide(Sides::TOP, textureTop);
    b->setTextureSide(Sides::BOTTOM, textureBottom);
    b->setTextureSide(Sides::LEFT, textureSide);
    b->setTextureSide(Sides::RIGHT, textureSide);
    b->setTextureSide(Sides::FRONT, textureSide);
    b->setTextureSide(Sides::BACK, textureSide);

    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    TestEntity(r,e);
}

void Tests::TestShapes(Renderer *r)
{
    OpenGLEntity *e = new OpenGLEntity();
    e->show();

    Plane2D *p = new Plane2D(e);
    p->translate(0.f,0.f,1.f);
    p->init();


    Triangle2D *t = new Triangle2D(e);
    t->translate(0.f,0.f,-1.f);
    t->init();

    TestEntity(r,e);
}


void Tests::TestEntity(Renderer *r, OpenGLEntity *e)
{
    std::cout << "Loading shaders" << std::endl;

    if(r->getProgramID() == 0)
    {
        //Shaders
        GLuint fragmentID = GLUtils::LoadShader("shaders/SimpleFragmentShader.fsh", GL_FRAGMENT_SHADER);
        GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

        //Program
        GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
        r->setProgram(programID);
    }

    std::cout << "Initializing models" << std::endl;
    Scene *s = new Scene(60.0f,float(r->getSize().x) / float(r->getSize().y),0.1f,100.0f);
    s->setVertexShader(r->getProgramID());

    r->setScene(s);
    s->setRoot(e);

    std::cout << "Running" << std::endl;
    r->start(60);

    while(r->isOpen())
    {
        sf::Event event;
        while (r->pollEvent(event))
        {
            // on regarde le type de l'évènement...
            switch (event.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    r->close();
                    break;

                // touche pressée
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) r->close();
                    break;

                // on ne traite pas les autres types d'évènements
                default:
                    break;
            }
        }
    }

    std::cout << "Exiting" << std::endl;
}
