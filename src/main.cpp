#include <iostream>

#include "opengl.h"

#include "engine/controller/renderersdl.h"
#include "tests.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{

    RendererSDL *r = new RendererSDL(800,600,"Renderer");

    if(!r->isInitialized())
    {
        std::cout << "The renderer could not be initialized properly" << std::endl;
        return -1;
    }

    #ifdef WIN32
    int res = glewInit();

    if(res != GLEW_OK){
        std::cout << "GLEW did not initialize properly : " << glewGetErrorString(res) << std::endl;
        return -1;
    }
    #endif

    std::cout << r->getOpenGlInfo() << std::endl;

    //Tests::TestBlocks(r,"textures/grass-side.jpg","textures/dirt.jpg","textures/grass.jpg");
    //Tests::TestChunk(r,0,0,128,"textures/grass-side.jpg","textures/dirt.jpg","textures/grass.jpg");
    //Tests::TestCulling(r,"textures/grass-side.jpg","textures/dirt.jpg","textures/grass.jpg",glm::vec3(5.0f,5.0f,5.0f));
    //Tests::TestJsonEntity(r, "entities/cube.json");
    Tests::TestInstancing(r,"textures/blaze.jpg",10,10);

    std::cout << "Closing Main loop" << std::endl;
    return 0;
}
