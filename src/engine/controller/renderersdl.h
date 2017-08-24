#ifndef RENDERERSDL_H
#define RENDERERSDL_H

#include "opengl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <thread>
#include <sstream>
#include <chrono>

#include "opengl/openglentity.h"
#include "opengl/scene.h"
#include "opengl/glutils.h"

#include "controller/renderer.h"

class RendererSDL : public Renderer
{
public:
    RendererSDL(int w, int h, std::string title);
    ~RendererSDL();

    void processInputs();
    bool isOpen();
    void renderFrame();

private:
    SDL_Window *window;
    SDL_GLContext context;
};

#endif // RENDERERSDL_H
