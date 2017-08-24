#include "renderer.h"

Renderer::Renderer(int w, int h)
{
    this->run = false;
    this->w = w;
    this->h = h;
}

std::string Renderer::getOpenGlInfo()
{
    std::ostringstream oss;
    oss << "GL_VENDOR : " << glGetString(GL_VENDOR) << std::endl;
    oss << "GL_RENDERER : " << glGetString(GL_RENDERER) << std::endl;
    oss << "GL_VERSION : " << glGetString(GL_VERSION) << std::endl;
    oss << "GL_SHADING_LANGUAGE_VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return oss.str();
}

void Renderer::setScene(Scene *s)
{
    this->scene = s;
}

void Renderer::setProgram(GLuint programID)
{
    this->programID = programID;
}

GLuint Renderer::getProgramID()
{
    return this->programID;
}

void Renderer::start(int fps)
{
    //this->thread = new std::thread(renderingThread,this,fps);
    this->run = true;
}

void Renderer::stop()
{
    this->run = false;
}

bool Renderer::isRunning()
{
    return this->run;
}

bool Renderer::isInitialized()
{
    return this->initialized;
}

void Renderer::init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Renderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(this->programID);

    //OpenGL
    auto started = std::chrono::high_resolution_clock::now();
    this->scene->draw();
    auto done = std::chrono::high_resolution_clock::now();

    glUseProgram(0);

    this->renderFrame();
}


int Renderer::getWidth()
{
    return this->w;
}

int Renderer::getHeight()
{
    return this->h;
}


void renderingThread(Renderer* renderer, int fps)
{
    while(renderer->isRunning())
    {
        renderer->update();
    }
}
