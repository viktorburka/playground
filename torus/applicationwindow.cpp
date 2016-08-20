#include "applicationwindow.h"
#include "shaderprogram.h"

#include <QDebug>
#include <QFile>

float degreeToRadians(float degree)
{
    return degree * 3.14159265 / 180.0;
}

ApplicationWindow::ApplicationWindow()
    : shaderProgram(0)
{
    shaderProgram = new ShaderProgram;
}

void ApplicationWindow::initializeGL()
{
    initializeOpenGLFunctions();

    qDebug() << "major: " << this->context()->format().majorVersion() << ", "
             << "minor: " << this->context()->format().minorVersion();

    QFile vsh("shaders/main_vsh.sh");
    if (!vsh.open(QIODevice::ReadOnly)) {
        qDebug() << "Error reading vertex shader file:" << vsh.fileName();
        exit(1);
    }

    QFile fsh("shaders/main_fsh.sh");
    if (!fsh.open(QIODevice::ReadOnly)) {
        qDebug() << "Error reading fragment shader file:" << fsh.fileName();
        exit(1);
    }

    QByteArray vertexShaderSource = vsh.readAll();
    QByteArray fragmentShaderSource = fsh.readAll();

    shaderProgram->init();
    shaderProgram->setVertexShaderSource(vertexShaderSource.constData());
    shaderProgram->setFragmentShaderSource(fragmentShaderSource.constData());

    if (!shaderProgram->build()) {
        printf("Shader build error: %s\n", shaderProgram->buildError().c_str());
        exit(1);
    }

    //    view.lookAt(QVector3D(0.0, 0.5, 0.5),
    //                QVector3D(0.0, 0.0, 0.0),
    //                QVector3D(0.0, 1.0, 0.0));

    m_viewMatrix.lookAt(QVector3D(-2.0, 0.0, 3.0),
                        QVector3D( 0.0, 0.0, 0.0),
                        QVector3D( 0.0, 1.0, 0.0));

    glEnable(GL_DEPTH_TEST);

    const float outerRadius = 1.0f;
    const float innerRadius = 0.2f;
    const float phiIncrement = 2.0f;
    const float tauIncrement = 5.0f;
    const int coordinatesNumber = 3;

    float phi = 0.0;
    float tau = 0.0;

    m_outerObjectsNumber = 360.0 / phiIncrement;
    m_innerObjectsNumber = 360.0 / tauIncrement;

    m_verticesNumber = m_innerObjectsNumber * 2 * m_outerObjectsNumber;

    GLfloat* coordinates = new GLfloat[m_verticesNumber * coordinatesNumber];

    GLfloat* p = coordinates;
    for (int i = 0; i < m_outerObjectsNumber; ++i) {
        for (int j = 0; j < m_innerObjectsNumber; ++j) {
            for (int k = 0; k < 2; ++k) {
                float tau_rad = degreeToRadians(tau);
                float phi_rad = degreeToRadians(phi + k*phiIncrement);
                *p++ = (outerRadius + innerRadius*cos(tau_rad))*cos(phi_rad);
                *p++ = (outerRadius + innerRadius*cos(tau_rad))*sin(phi_rad);
                *p++ = innerRadius*sin(tau_rad);
            }
            tau += tauIncrement;
        }
        tau = 0.0;
        phi += phiIncrement;
    }

    glGenBuffers(1, &m_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
    glBufferData(GL_ARRAY_BUFFER, m_verticesNumber * coordinatesNumber * sizeof(GLfloat),
                 coordinates, GL_DYNAMIC_DRAW);

    delete [] coordinates;
}

void ApplicationWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgram->programId());

    GLint uniModel = glGetUniformLocation(shaderProgram->programId(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, m_modelMatrix.constData());

    GLint uniView = glGetUniformLocation(shaderProgram->programId(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, m_viewMatrix.constData());

    GLint uniProj = glGetUniformLocation(shaderProgram->programId(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, m_projMatrix.constData());

    GLint posAttrib = shaderProgram->getAttribLocation("position");
    glEnableVertexAttribArray(posAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindFragDataLocation(shaderProgram->programId(), 0, "outColor");
    //glDrawArrays(GL_POINTS, 0, m_verticesNumber);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, m_verticesNumber);
}

void ApplicationWindow::resizeEvent(QResizeEvent *e)
{
    m_projMatrix.setToIdentity();
    m_projMatrix.perspective(60.0, width()/height(), 0.1f, 100.f);
    QOpenGLWindow::resizeEvent(e);
}

