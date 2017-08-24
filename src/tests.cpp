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

void Tests::TestTexturePlacement(Renderer *r, std::string file)
{
    OpenGLEntity *e = new OpenGLEntity();
    e->show();

    OpenGLTexture *texture = new OpenGLTexture(file);

    Plane2D *p = new Plane2D(e);
    p->init();
    p->setTexture(texture);

    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    TestEntity(r,e);
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

void Tests::TestBlocks(Renderer *r, std::string texSide, std::string texBottom, std::string texTop)
{
    OpenGLEntity *e = new OpenGLEntity();
    e->show();

    OpenGLTexture *textureTop = new OpenGLTexture(texTop);
    OpenGLTexture *textureBottom = new OpenGLTexture(texBottom);
    OpenGLTexture *textureSide = new OpenGLTexture(texSide);

    Box3D *b1 = new Box3D(e);
    b1->init();

    b1->setTextureSide(Sides::TOP, textureTop);
    b1->setTextureSide(Sides::BOTTOM, textureBottom);
    b1->setTextureSide(Sides::LEFT, textureSide);
    b1->setTextureSide(Sides::RIGHT, textureSide);
    b1->setTextureSide(Sides::FRONT, textureSide);
    b1->setTextureSide(Sides::BACK, textureSide);

    b1->translate(0.0f,0.0f,-1.0f);
    b1->scale(0.5f);

    Box3D *b2 = new Box3D(e);
    b2->init();

    b2->setTextureSide(Sides::TOP, textureTop);
    b2->setTextureSide(Sides::BOTTOM, textureBottom);
    b2->setTextureSide(Sides::LEFT, textureSide);
    b2->setTextureSide(Sides::RIGHT, textureSide);
    b2->setTextureSide(Sides::FRONT, textureSide);
    b2->setTextureSide(Sides::BACK, textureSide);

    b2->scale(0.5f);

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
    Scene *s = new Scene(60.0f,float(r->getWidth()) / float(r->getHeight()));
    s->setVertexShader(r->getProgramID());

    r->setScene(s);
    s->setRoot(e);

    std::cout << "Running" << std::endl;
    r->start(60);

    GLUtils::OutputErrors("Initialization");

    while(r->isRunning())
    {
        r->processInputs();
        r->update();

        GLUtils::OutputErrors("Loop");
    }


    std::cout << "Exiting" << std::endl;
}
