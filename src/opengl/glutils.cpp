#include "glutils.h"

GLUtils::GLUtils()
{

}

GLuint GLUtils::LoadShader(const char * file_path, GLenum shaderType)
{
    GLuint ShaderID = glCreateShader(shaderType);

    // Read the Shader code from the file
    std::string ShaderCode;
    std::ifstream ShaderStream(file_path, std::ios::in);
    if(ShaderStream.is_open()){
        std::string Line = "";
        while(getline(ShaderStream, Line))
            ShaderCode += "\n" + Line;
        ShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", file_path);
    char const * SourcePointer = ShaderCode.c_str();
    glShaderSource(ShaderID, 1, &SourcePointer , NULL);
    glCompileShader(ShaderID);

    // Check Vertex Shader
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
        printf("%s\n", &ShaderErrorMessage[0]);
    }
    return ShaderID;
}

GLuint GLUtils::LoadShaders(GLuint VertexShaderID, GLuint FragmentShaderID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);


    return ProgramID;
}

GLuint GLUtils::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
    GLuint vertex = LoadShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint fragment = LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

    return LoadShaders(vertex,fragment);
}

std::string GLUtils::GetErrors()
{
    std::ostringstream oss;

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      //Process/log the error.
        oss << "Error " << err << " : ";
        switch(err)
        {
        case GL_INVALID_ENUM:
            oss << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            oss << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            oss << "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            oss << "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            oss << "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            oss << "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            oss << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_CONTEXT_LOST:
            oss << "GL_CONTEXT_LOST";
            break;
        default:
            oss << "Unhandled error";
            break;
        }

        oss << std::endl;
    }

    return oss.str();
}
