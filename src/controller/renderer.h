#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <vector>
#include <thread>
#include <sstream>
#include <chrono>

#include "opengl/openglentity.h"
#include "opengl/scene.h"
#include "opengl/glutils.h"

class Renderer : public sf::RenderWindow
{
public:
    Renderer(int w, int h, std::string title);
    void setScene(Scene *s);

    void setProgram(GLuint programID);
    void start(int fps);
    void stop();
    void update();

    void drawLatency(int us);

    bool isRunning();

    GLuint getProgramID();

private:
    GLuint programID = 0;

    Scene *scene = 0;
    std::thread *thread;
    bool run;

    sf::Font font;
};

void renderingThread(Renderer* renderer, int fps);
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif // RENDERER_H
