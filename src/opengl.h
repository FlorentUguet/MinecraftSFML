#ifndef OPENGL_H
#define OPENGL_H

#ifdef WIN32
    #include <GL/glew.h>
#else
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>
#endif

#include <GL/glu.h>

#endif // OPENGL_H
