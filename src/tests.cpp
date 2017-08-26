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

    OpenGLTexture *textureTop = new OpenGLTexture(texTop, GL_RGB);
    OpenGLTexture *textureBottom = new OpenGLTexture(texBottom, GL_RGB);
    OpenGLTexture *textureSide = new OpenGLTexture(texSide, GL_RGB);

    Box3D *b1 = new Box3D(e);
    b1->init();

    b1->setTextureSide(Box3D::Sides::TOP, textureTop);
    b1->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
    b1->setTextureSide(Box3D::Sides::LEFT, textureSide);
    b1->setTextureSide(Box3D::Sides::RIGHT, textureSide);
    b1->setTextureSide(Box3D::Sides::FRONT, textureSide);
    b1->setTextureSide(Box3D::Sides::BACK, textureSide);

    b1->translate(0.0f,0.0f,-1.0f);
    b1->scale(0.5f);

    Box3D *b2 = new Box3D(e);
    b2->init();

    b2->setTextureSide(Box3D::Sides::TOP, textureTop);
    b2->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
    b2->setTextureSide(Box3D::Sides::LEFT, textureSide);
    b2->setTextureSide(Box3D::Sides::RIGHT, textureSide);
    b2->setTextureSide(Box3D::Sides::FRONT, textureSide);
    b2->setTextureSide(Box3D::Sides::BACK, textureSide);

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


void Tests::TestEntity(Renderer *r, OpenGLEntity *e, bool oneShot, bool measure)
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



    do
    {
        auto started = std::chrono::high_resolution_clock::now();
        r->processInputs();
        r->update();
        auto done = std::chrono::high_resolution_clock::now();
        int t = std::chrono::duration_cast<std::chrono::milliseconds>( done - started ).count();
        if(measure) std::cout << "Frame rendered in " << t << "ms (" << 1000.0 / double(t) << " fps)"<< std::endl;

        GLUtils::OutputErrors("Loop");
    }while(r->isRunning() && !oneShot);


    std::cout << "Exiting" << std::endl;
}

void Tests::TestChunk(Renderer *r, int x, int y, unsigned int seed, std::string texSide, std::string texBottom, std::string texTop)
{
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    OpenGLEntity *e = new OpenGLEntity();

    auto started = std::chrono::high_resolution_clock::now();
    ChunkEntity *c = new ChunkEntity(x,y);
    c->generate(seed);
    auto done = std::chrono::high_resolution_clock::now();

    std::cout << "Generated chunk in " << std::chrono::duration_cast<std::chrono::milliseconds>( done - started ).count() << "ms" << std::endl;

    std::vector<BlockEntity*> blocks = c->getBlocks();

    OpenGLTexture *textureTop = new OpenGLTexture(texTop, GL_RGB);
    OpenGLTexture *textureBottom = new OpenGLTexture(texBottom, GL_RGB);
    OpenGLTexture *textureSide = new OpenGLTexture(texSide, GL_RGB);

    //Without side optimization
    std::cout << std::endl << "Without optimization" << std::endl;
    started = std::chrono::high_resolution_clock::now();
    for(int i=0;i<blocks.size();i++)
    {
        BlockEntity *b = blocks[i];
        Box3D *box = new Box3D(e);
        box->init();
        box->translate(b->getAbsX(),b->getAbsY(),b->getAbsZ());
        box->scale(0.5f);

        box->setTextureSide(Box3D::Sides::TOP, textureTop);
        box->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
        box->setTextureSide(Box3D::Sides::LEFT, textureSide);
        box->setTextureSide(Box3D::Sides::RIGHT, textureSide);
        box->setTextureSide(Box3D::Sides::FRONT, textureSide);
        box->setTextureSide(Box3D::Sides::BACK, textureSide);
    }
    done = std::chrono::high_resolution_clock::now();
    std::cout << "Loaded entities in " << std::chrono::duration_cast<std::chrono::milliseconds>( done - started ).count() << "ms" << std::endl;;
    TestEntity(r,e, true, true);
    delete e;

    //With side optimization
    e = new OpenGLEntity();
    std::cout << std::endl << "With unseen blocks hidden" << std::endl;
    started = std::chrono::high_resolution_clock::now();

    int visible = 0;
    for(int i=0;i<blocks.size();i++)
    {
        BlockEntity *b = blocks[i];
        b->updateBlockVisibility();

        if(b->isVisible())
        {
            Box3D *box = new Box3D(e);
            box->init();
            box->translate(b->getAbsX(),b->getAbsY(),b->getAbsZ());
            box->scale(0.5f);

            box->setTextureSide(Box3D::Sides::TOP, textureTop);
            box->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
            box->setTextureSide(Box3D::Sides::LEFT, textureSide);
            box->setTextureSide(Box3D::Sides::RIGHT, textureSide);
            box->setTextureSide(Box3D::Sides::FRONT, textureSide);
            box->setTextureSide(Box3D::Sides::BACK, textureSide);

            visible+=6; //6 sides
        }
    }
    done = std::chrono::high_resolution_clock::now();
    std::cout << "Loaded " << visible << " visible entities in " << std::chrono::duration_cast<std::chrono::milliseconds>( done - started ).count() << "ms" << std::endl;;
    TestEntity(r,e, true, true);
    delete e;

    //With side optimization
    e = new OpenGLEntity();
    std::cout << std::endl << "With unseen sides and blocks hidden" << std::endl;
    started = std::chrono::high_resolution_clock::now();

    visible = 0;
    for(int i=0;i<blocks.size();i++)
    {
        BlockEntity *b = blocks[i];
        b->updateBlockVisibility();

        if(b->isVisible())
        {
            b->updateVisibility();

            Box3D *box = new Box3D(e);
            box->init();
            box->translate(b->getAbsX(),b->getAbsY(),b->getAbsZ());
            box->scale(0.5f);

            box->setTextureSide(Box3D::Sides::TOP, textureTop);
            box->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
            box->setTextureSide(Box3D::Sides::LEFT, textureSide);
            box->setTextureSide(Box3D::Sides::RIGHT, textureSide);
            box->setTextureSide(Box3D::Sides::FRONT, textureSide);
            box->setTextureSide(Box3D::Sides::BACK, textureSide);

            std::vector<BlockSideEntity*> sides = b->getSides();

            for(int i=0;i<Box3D::Sides::COUNT;i++)
            {
                box->setSideVisible(i, sides[i]->isVisible());
                if(sides[i]->isVisible()) visible++;
            }
        }
    }
    done = std::chrono::high_resolution_clock::now();
    std::cout << "Loaded " << visible << " visible entities in " << std::chrono::duration_cast<std::chrono::milliseconds>( done - started ).count() << "ms" << std::endl;;
    TestEntity(r,e, true, true);

}
