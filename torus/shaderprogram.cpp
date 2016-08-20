#include "shaderprogram.h"

ShaderProgram::ShaderProgram()
{
}

void ShaderProgram::setVertexShaderSource(const char * source)
{
    glShaderSource(vertexShaderId, 1, &source, NULL);
}

void ShaderProgram::setFragmentShaderSource(const char * source)
{
    glShaderSource(fragmentShaderId, 1, &source, NULL);
}

void ShaderProgram::init()
{
    initializeOpenGLFunctions();
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
}

bool ShaderProgram::build()
{
    GLint status;

    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vertexShaderId, 512, NULL, buffer);
        buildErrorString = buffer;
        return false;
    }

    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, buffer);
        buildErrorString = buffer;
        return false;
    }

    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    return true;
}

std::string ShaderProgram::buildError() const
{
    return buildErrorString;
}

GLuint ShaderProgram::programId() const
{
    return shaderProgramId;
}

GLint ShaderProgram::getAttribLocation(const char * name)
{
    return glGetAttribLocation(shaderProgramId, name);
}
