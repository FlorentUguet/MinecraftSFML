#include "renderersdl.h"

RendererSDL::RendererSDL(int w, int h, std::string title) : Renderer(w,h)
{
    if (SDL_Init (SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0){
        std::cout << SDL_GetError() << std::endl;
        return;
    }

    if (IMG_Init(IMG_INIT_JPG) < 0){
        std::cout << IMG_GetError() << std::endl;
        return;
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE | SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //SDL_GL_SetSwapInterval(1);

    //Window
    this->window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(this->window == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();

        return;
    }

    //Context
    this->context = SDL_GL_CreateContext(this->window);

    if(this->context == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(this->window);
        SDL_Quit();

        return;
    }

    this->init();
    this->initialized = true;
}

RendererSDL::~RendererSDL()
{
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();
}

void RendererSDL::processInputs()
{
    SDL_Event event;

    SDL_WaitEvent(&event);

    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
    {
        this->stop();
    }
    else if(event.type == SDL_KEYDOWN)
    {
        std::cout << "You just pressed the " << (char)event.key.keysym.sym << " key" << std::endl;
    }
    else if(event.type == SDL_KEYUP)
    {
        std::cout << "You just released the " << (char)event.key.keysym.sym << " key" << std::endl;
    }
}

bool RendererSDL::isOpen()
{
    return (SDL_GetWindowFlags(this->window) & SDL_WINDOW_SHOWN);
}

void RendererSDL::renderFrame()
{
    SDL_GL_SwapWindow(this->window);
}
