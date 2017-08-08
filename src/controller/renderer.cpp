#include "renderer.h"

Renderer::Renderer(int w, int h, std::string title) :sf::RenderWindow(sf::VideoMode(w,h),title)
{
    this->run = false;

    if (!this->font.loadFromFile("fonts/arial.ttf"))
    {
        std::cout << "Could not load font" << std::endl;
    }
}

void Renderer::setScene(Scene *s)
{
    this->scene = s;
}

void Renderer::setProgram(GLuint programID)
{
    this->programID = programID;
}

void Renderer::start()
{
    this->setActive(false);
    this->thread = new std::thread(renderingThread,this);
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

void Renderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(this->programID != 0)
        glUseProgram(this->programID);

    //OpenGL
    auto started = std::chrono::high_resolution_clock::now();
    this->scene->draw();
    auto done = std::chrono::high_resolution_clock::now();

    //SFML
    this->pushGLStates();
    drawLatency(std::chrono::duration_cast<std::chrono::microseconds>(done-started).count());
    this->popGLStates();

    this->display();
}

void Renderer::drawLatency(int us)
{
    std::ostringstream oss;
    oss << us/1000 << "." << us%1000 << " ms";

    sf::Text text = sf::Text(oss.str(),this->font,10);
    text.setFillColor(sf::Color::White);

    std::cout << oss.str() << std::endl;

    this->draw(text);
}

void renderingThread(Renderer* renderer)
{
    renderer->setActive(true);

    while(renderer->isOpen() && renderer->isRunning())
    {
        renderer->update();
    }
}
