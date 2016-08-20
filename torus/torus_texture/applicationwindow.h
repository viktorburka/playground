#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include <QMatrix4x4>

class ShaderProgram;

class ApplicationWindow: public QOpenGLWindow, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    ApplicationWindow();

protected:
    void initializeGL();
    void paintGL();

    void resizeEvent(QResizeEvent *e);

private:
    ShaderProgram* shaderProgram;

    QMatrix4x4 m_modelMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_projMatrix;

    GLuint m_vertices;
    GLuint m_textureBuffer;
    GLuint m_textureId;
    int m_innerObjectsNumber;
    int m_outerObjectsNumber;
    int m_verticesNumber;
};

#endif // APPLICATIONWINDOW_H
