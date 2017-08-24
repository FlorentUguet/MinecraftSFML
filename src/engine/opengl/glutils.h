#ifndef GLUTILS_H
#define GLUTILS_H

#include "opengl.h"

#include "openglentity.h"

#include <iostream>
#include <fstream>
#include <sstream>

class GLUtils
{
public:
    GLUtils();
    static GLuint LoadShader(const char * file_path, GLenum shaderType);
    static GLuint LoadShaders(GLuint VertexShaderID, GLuint FragmentShaderID);
    static GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
    static void OutputErrors(std::string label);
    static std::string GetErrors();
};

#endif // GLUTILS_H
