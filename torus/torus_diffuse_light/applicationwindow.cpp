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
    const float phiIncrement = 1.0f;
    const float tauIncrement = 1.0f;
    const int coordinatesNumber = 3;

    float phi = 0.0;
    float tau = 0.0;

    m_outerObjectsNumber = 360.0 / phiIncrement;
    m_innerObjectsNumber = 360.0 / tauIncrement;

    m_verticesNumber = m_innerObjectsNumber * 6 * m_outerObjectsNumber;

    GLfloat* coordinates = new GLfloat[m_verticesNumber * coordinatesNumber];

    GLfloat* p = coordinates;
    for (int i = 0; i < m_outerObjectsNumber; ++i) {
        for (int j = 0; j < m_innerObjectsNumber; ++j) {
            //for (int k = 0; k < 2; ++k) {
            float tau_rad = degreeToRadians(tau);
            float phi_rad = degreeToRadians(phi);
            float tau_inc_rad = degreeToRadians(tau + tauIncrement);
            float phi_inc_rad = degreeToRadians(phi + phiIncrement);
            // v1
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*cos(phi_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*sin(phi_rad);
            *p++ = innerRadius*sin(tau_rad);
            // v2
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*cos(phi_inc_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*sin(phi_inc_rad);
            *p++ = innerRadius*sin(tau_rad);
            // v3
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*cos(phi_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*sin(phi_rad);
            *p++ = innerRadius*sin(tau_inc_rad);
            // v4
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*cos(phi_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*sin(phi_rad);
            *p++ = innerRadius*sin(tau_inc_rad);
            // v5
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*cos(phi_inc_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_rad))*sin(phi_inc_rad);
            *p++ = innerRadius*sin(tau_rad);
            // v6
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*cos(phi_inc_rad);
            *p++ = (outerRadius + innerRadius*cos(tau_inc_rad))*sin(phi_inc_rad);
            *p++ = innerRadius*sin(tau_inc_rad);
            //}
            tau += tauIncrement;
        }
        tau = 0.0;
        phi += phiIncrement;
    }

    glGenBuffers(1, &m_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
    glBufferData(GL_ARRAY_BUFFER, m_verticesNumber * coordinatesNumber * sizeof(GLfloat),
                 coordinates, GL_DYNAMIC_DRAW);

    GLfloat* normals = new GLfloat[m_verticesNumber * coordinatesNumber];
    qDebug() << "sizeof normals = " << m_verticesNumber * coordinatesNumber;

    int j = 0;
    for (int i = 0; i < m_verticesNumber * coordinatesNumber - coordinatesNumber*3; i += coordinatesNumber*3) {
        QVector3D v1 = QVector3D(coordinates[i+3], coordinates[i+4], coordinates[i+5]) - QVector3D(coordinates[i], coordinates[i+1], coordinates[i+2]);
        QVector3D v2 = QVector3D(coordinates[i+6], coordinates[i+7], coordinates[i+8]) - QVector3D(coordinates[i], coordinates[i+1], coordinates[i+2]);
        QVector3D normal = QVector3D::normal(v1, v2);
        for (int k = 0; k < 3; ++k) {
            normals[j++] = normal.x();
            normals[j++] = normal.y();
            normals[j++] = normal.z();
        }
    }

    glGenBuffers(1, &m_normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_verticesNumber * coordinatesNumber * sizeof(GLfloat),
                 normals, GL_DYNAMIC_DRAW);

    delete [] normals;
    delete [] coordinates;

    GLfloat textureCoordinates[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    // green
    GLuint texture[] = {
        0xFF00AA00, 0xFF00AA00,
        0xFF00AA00, 0xFF00AA00
    };

    glGenBuffers(1, &m_textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates),
                 textureCoordinates, GL_DYNAMIC_DRAW);

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 2, 2,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ApplicationWindow::paintGL()
{
    QVector3D lightColor(1.0, 1.0, 1.0);
    GLfloat ambientIntensity = 0.1f;
    GLfloat diffuseIntensity = 0.8f;

    QVector3D direction(1.0f, 1.0f, 1.0f);
    direction.normalize();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgram->programId());

    GLint uniModel = glGetUniformLocation(shaderProgram->programId(), "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, m_modelMatrix.constData());

    GLint uniView = glGetUniformLocation(shaderProgram->programId(), "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, m_viewMatrix.constData());

    GLint uniProj = glGetUniformLocation(shaderProgram->programId(), "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, m_projMatrix.constData());

    GLint uniLightColor = glGetUniformLocation(shaderProgram->programId(), "lightColor");
    glUniform3f(uniLightColor, lightColor.x(), lightColor.y(), lightColor.z());

    GLint uniAmbientIntensity = glGetUniformLocation(shaderProgram->programId(), "ambientIntensity");
    glUniform1f(uniAmbientIntensity, ambientIntensity);

    GLint uniDiffuseIntensity = glGetUniformLocation(shaderProgram->programId(), "diffuseIntensity");
    glUniform1f(uniDiffuseIntensity, diffuseIntensity);

    GLint uniLightDirection = glGetUniformLocation(shaderProgram->programId(), "lightDirection");
    glUniform3f(uniLightDirection, direction.x(), direction.y(), direction.z());

    GLint posAttrib = shaderProgram->getAttribLocation("position");
    glEnableVertexAttribArray(posAttrib);

    GLint texAttrib = shaderProgram->getAttribLocation("texcoord");
    glEnableVertexAttribArray(texAttrib);

    GLint normalAttrib = shaderProgram->getAttribLocation("normal");
    glEnableVertexAttribArray(normalAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_normalsBuffer);
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glBindFragDataLocation(shaderProgram->programId(), 0, "outColor");

    glDrawArrays(GL_TRIANGLES, 0, m_verticesNumber);
}

void ApplicationWindow::resizeEvent(QResizeEvent *e)
{
    m_projMatrix.setToIdentity();
    m_projMatrix.perspective(60.0, width()/height(), 0.1f, 100.f);
    QOpenGLWindow::resizeEvent(e);
}

