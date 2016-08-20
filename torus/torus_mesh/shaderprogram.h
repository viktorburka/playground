#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLFunctions_4_3_Core>

class ShaderProgram: protected QOpenGLFunctions_4_3_Core
{
public:
    ShaderProgram();

    void setVertexShaderSource(const char * source);
    void setFragmentShaderSource(const char * source);

    void init();
    bool build();

    std::string buildError() const;
    GLuint programId() const;

    GLint getAttribLocation(const char * name);

private:
    GLuint vertexShaderId;
    GLuint fragmentShaderId;
    GLuint shaderProgramId;
    std::string buildErrorString;
};

#endif // SHADERPROGRAM_H
