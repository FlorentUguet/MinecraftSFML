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


void Tests::TestEntity(Renderer *r, OpenGLEntity *e, Camera *c, int loops, bool measure)
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

    if(c == 0)
    {
        c = new Camera();
        c->setParent(e);
        c->translate(4.0f,4.0f,4.0f);
    }

    Scene *s = new Scene(c,e);

    s->setVertexShader(r->getProgramID());
    r->setScene(s);

    std::cout << "Running" << std::endl;
    r->start(60);

    GLUtils::OutputErrors("Initialization");

    Timer t;
    int loop = 0;

    do
    {
        t.start();
            r->processInputs();
            r->update();
        t.stop();
        GLUtils::OutputErrors("Loop");
        loop++;
    }while(r->isRunning() && (loops <= 0 || loop < loops));

    int time = t.getElapsedMS() / loop;
    if(measure) std::cout << loop << " frames rendered in " << time << "ms (" << 1000.0 / double(time) << " fps)"<< std::endl;

    std::cout << "Exiting" << std::endl;
}

void Tests::TestChunk(Renderer *r, int x, int y, unsigned int seed, std::string texSide, std::string texBottom, std::string texTop)
{
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    Timer t;
    int loops = 2;
    Camera *c;
    glm::vec3 cameraPos = glm::vec3(32.0f,64.0f,32.0f);

    OpenGLEntity *e = new OpenGLEntity();

    t.start();
    ChunkEntity *chunk = new ChunkEntity(x,y);
    chunk->generate(seed);
    t.stop();

    std::cout << "Generated chunk in " << t.getElapsedMS() << "ms" << std::endl;

    std::vector<BlockEntity*> blocks = chunk->getBlocks();

    OpenGLTexture *textureTop = new OpenGLTexture(texTop, GL_RGB);
    OpenGLTexture *textureBottom = new OpenGLTexture(texBottom, GL_RGB);
    OpenGLTexture *textureSide = new OpenGLTexture(texSide, GL_RGB);
    //Without side optimization
    std::cout << std::endl << "Without optimization" << std::endl;
    t.restart();
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
    t.stop();
    std::cout << "Loaded entities in " << t.getElapsedMS() << "ms" << std::endl;

    c = new Camera();
    c->setParent(e);
    c->translate(cameraPos);

    TestEntity(r, e, c, loops, true);
    delete e;

    //With side optimization
    e = new OpenGLEntity();
    std::cout << std::endl << "With unseen blocks hidden" << std::endl;
    t.restart();

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
    t.stop();
    std::cout << "Loaded " << visible << " visible entities in " << t.getElapsedMS() << "ms" << std::endl;

    c = new Camera();
    c->setParent(e);
    c->translate(cameraPos);

    TestEntity(r, e, c, loops, true);
    delete e;

    //With side optimization
    e = new OpenGLEntity();
    std::cout << std::endl << "With unseen sides and blocks hidden" << std::endl;
    t.restart();

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
    t.stop();
    std::cout << "Loaded " << visible << " visible entities in " << t.getElapsedMS() << "ms" << std::endl;

    c = new Camera();
    c->setParent(e);
    c->translate(cameraPos);

    TestEntity(r,e, c, loops, true);

    //With culling
    glEnable(GL_CULL_FACE);
    e = new OpenGLEntity();
    std::cout << std::endl << "With culling" << std::endl;
    t.restart();

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
    t.stop();
    std::cout << "Loaded " << visible << " visible entities in " << t.getElapsedMS() << "ms" << std::endl;

    c = new Camera();
    c->setParent(e);
    c->translate(cameraPos);

    TestEntity(r,e, c, loops, true);
}

void Tests::TestCulling(Renderer *r, std::string texSide, std::string texBottom, std::string texTop, glm::vec3 cameraPos)
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

    Box3D *b3 = new Box3D(e);
    b3->init();

    b3->setTextureSide(Box3D::Sides::TOP, textureTop);
    b3->setTextureSide(Box3D::Sides::BOTTOM, textureBottom);
    b3->setTextureSide(Box3D::Sides::LEFT, textureSide);
    b3->setTextureSide(Box3D::Sides::RIGHT, textureSide);
    b3->setTextureSide(Box3D::Sides::FRONT, textureSide);
    b3->setTextureSide(Box3D::Sides::BACK, textureSide);

    b3->translate(-1.0f,1.0f,-1.0f);
    b3->rotate(0.0f,90.0f,0.0f);
    b3->scale(0.5f);

    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    Camera *c = new Camera();
    c->setParent(e);
    c->translate(cameraPos);

    int loops = 500;

    std::cout << std::endl << "Without culling " << std::endl;
    TestEntity(r,e,c,loops,true);

    glEnable(GL_CULL_FACE);
    std::cout << std::endl << "With culling " << std::endl;
    TestEntity(r,e,c,loops,true);
}

void Tests::TestBlockPlane(Renderer *r, std::string texture, int x, int y, bool culling)
{
    OpenGLTexture *tex = new OpenGLTexture(texture, GL_RGB);
    OpenGLEntity *e = new OpenGLEntity();

    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            Box3D *b = new Box3D(e);
            b->init();
            for(int k=0;k<Box3D::Sides::COUNT;k++)
                b->setTextureSide(k,tex);
            b->translate(-i,0.0f,-j);
            b->scale(0.5f);
        }
    }

    //Shaders
    GLuint fragmentID = GLUtils::LoadShader("shaders/TextureFSH.fsh", GL_FRAGMENT_SHADER);
    GLuint vertexID = GLUtils::LoadShader("shaders/MVPVSH.vsh", GL_VERTEX_SHADER);

    //Program
    GLuint programID = GLUtils::LoadShaders(vertexID,fragmentID);
    r->setProgram(programID);

    if(culling)
        glEnable(GL_CULL_FACE);

    Camera *c = new Camera();
    c->setParent(e);
    c->translate(glm::vec3(5.0f,5.0f,5.0f));

    TestEntity(r,e,c,200,true);
}


