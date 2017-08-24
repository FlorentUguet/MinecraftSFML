#ifndef RENDERER_H
#define RENDERER_H

#include "opengl.h"

#include <vector>
#include <thread>
#include <sstream>
#include <chrono>

#include "../opengl/openglentity.h"
#include "../opengl/scene.h"
#include "../opengl/glutils.h"

class Renderer
{
public:
    Renderer(int w, int h);

    static std::string getOpenGlInfo();

    void setScene(Scene *s);
    void setProgram(GLuint programID);
    void start(int fps);
    void stop();
    void update();
    void init();

    //Library Specific
    virtual void processInputs() = 0;
    virtual void renderFrame() = 0;
    virtual bool isOpen() = 0;

    int getWidth();
    int getHeight();

    bool isRunning();
    bool isInitialized();

    GLuint getProgramID();

protected:
    GLuint programID = 0;

    Scene *scene = 0;
    std::thread *thread;
    bool run;

    bool initialized = false;

    int w;
    int h;
};

void renderingThread(Renderer* renderer, int fps);
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif // RENDERER_H
