#include "applicationwindow.h"
#include "shaderprogram.h"

#include <QDebug>
#include <QFile>
#include <QWheelEvent>

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

//    m_viewMatrix.lookAt(QVector3D(0.0, 0.0, 3.0),
//                QVector3D(0.0, 0.0, 0.0),
//                QVector3D(0.0, 1.0, 0.0));

//    m_viewMatrix.lookAt(QVector3D(-2.0, 0.0, 3.0),
//                        QVector3D( 0.0, 0.0, 0.0),
//                        QVector3D( 0.0, 1.0, 0.0));

    glEnable(GL_DEPTH_TEST);

    const float outerRadius = 1.0f;
    const float innerRadius = 0.2f;
    const float phiIncrement = 20.0f;
    const float tauIncrement = 30.0f;
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

    GLfloat textureCoordinates[] = {
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };

    glGenBuffers(1, &m_textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates),
                 textureCoordinates, GL_DYNAMIC_DRAW);

    GLuint texture[] = {
        0x00FF00FF, 0x00FF00FF,
        0x00FF00FF, 0x00FF00FF
    };

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 2, 2,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ApplicationWindow::wheelEvent(QWheelEvent *e)
{
    zoomStart.setY(zoomStart.y() - e->delta() * 0.00025);
    update();
}

void ApplicationWindow::mousePressEvent(QMouseEvent *e)
{
    if (state == State::NONE) {
        state = mouseButtonToState(e->button());
    }

    if ( state == State::ROTATE ) {
        moveCurr = getMouseOnCircle(e->pos().x(), e->pos().y());
        movePrev = moveCurr;
    } else if ( state == State::ZOOM ) {
//        _zoomStart.copy( getMouseOnScreen( event.pageX, event.pageY ) );
//        _zoomEnd.copy( _zoomStart );
    } else if ( state == State::PAN ) {
        panStart = getMouseOnScreen(e->pos().x(), e->pos().y());
        panEnd = panStart;
    }
}

void ApplicationWindow::mouseMoveEvent(QMouseEvent * e)
{
    if ( state == State::ROTATE ) {

        movePrev = moveCurr;
        moveCurr = getMouseOnCircle( e->pos().x(), e->pos().y() );
        update();

    } else if ( state == State::ZOOM ) {

//        _zoomEnd.copy( getMouseOnScreen( event.pageX, event.pageY ) );

    } else if ( state == State::PAN ) {

        panEnd = getMouseOnScreen( e->pos().x(), e->pos().y() );
        update();
        qDebug() << "pan";
    }
}

void ApplicationWindow::mouseReleaseEvent(QMouseEvent *)
{
    state = State::NONE;
}

void ApplicationWindow::zoomCamera()
{
    double factor;
    factor = 1.0 + ( zoomEnd.y() - zoomStart.y() ) * zoomSpeed;

    if ( factor != 1.0 && factor > 0.0 ) {
        eye *= factor;
    }

    if ( staticMoving ) {
        zoomStart = zoomEnd;
    } else {
        zoomStart.setY( zoomStart.y() + (zoomEnd.y() - zoomStart.y()) * dynamicDampingFactor );
    }
}

void ApplicationWindow::rotateCamera()
{
    QVector3D axis;
    QQuaternion quaternion;
    QVector3D eyeDirection;
    QVector3D objectUpDirection;
    QVector3D objectSidewaysDirection;
    QVector3D moveDirection;
    double angle;

    moveDirection.setX(moveCurr.x() - movePrev.x());
    moveDirection.setY(moveCurr.y() - movePrev.y());
    moveDirection.setZ(0);

    angle = moveDirection.length();

    //if (angle > 0.0) {

        eye = cameraPosition - target;

        eyeDirection = eye;
        eyeDirection.normalize();

        objectUpDirection = cameraUp;
        objectUpDirection.normalize();

        objectSidewaysDirection = QVector3D::crossProduct(objectUpDirection, eyeDirection);
        objectSidewaysDirection.normalize();

        objectUpDirection.normalize();
        objectUpDirection *= (moveCurr.y() - movePrev.y());

        objectSidewaysDirection.normalize();
        objectSidewaysDirection *= (moveCurr.x() - movePrev.x());

        objectUpDirection += objectSidewaysDirection;
        moveDirection = objectUpDirection;

        axis = QVector3D::crossProduct(moveDirection, eye);
        axis.normalize();

        angle *= rotateSpeed;

        quaternion = QQuaternion::fromAxisAndAngle(axis, angle);

        eye = quaternion * eye;
        cameraUp = quaternion * cameraUp;

        lastAxis = axis;
        lastAngle = angle;
    //}

    movePrev = moveCurr;
}

void ApplicationWindow::panCamera()
{
    QVector2D mouseChange;
    QVector3D objectUp;
    QVector3D pan;

    mouseChange = panEnd;
    mouseChange -= panStart;

    if (mouseChange.lengthSquared() > 0.0) {

        mouseChange *= (eye.length() * panSpeed);

        pan = eye;
        pan = QVector3D::crossProduct(pan, cameraUp);
        pan.normalize();
        pan *= mouseChange.x();

        objectUp = cameraUp;
        objectUp.normalize();
        objectUp *= mouseChange.y();
        pan += objectUp;

        cameraPosition += pan;
        target += pan;

        if (staticMoving) {
            panStart = panEnd;
        } else {
//            _panStart.add( mouseChange.subVectors( _panEnd, _panStart ).multiplyScalar( _this.dynamicDampingFactor ) );
        }
    }
}

ApplicationWindow::State
ApplicationWindow::mouseButtonToState(Qt::MouseButton button) const
{
    switch(button) {
    case Qt::LeftButton:
        return State::ROTATE;
    case Qt::MiddleButton:
        return State::ZOOM;
    case Qt::RightButton:
        return State::PAN;
    default:
        return State::NONE;
    }
}

QVector2D ApplicationWindow::getMouseOnCircle(int pageX, int pageY) const
{
    QVector2D vector;
    vector.setX( ( pageX - this->width() * 0.5 ) / ( this->width() * 0.5 ) );
    vector.setY( ( this->height() + 2 * ( -pageY ) ) / double(this->width()) );
    return vector;
}

QVector2D ApplicationWindow::getMouseOnScreen(int pageX, int pageY) const
{
    QVector2D vector;
    vector.setX( pageX / double(this->width()) );
    vector.setY( pageY / double(this->height()) );
    return vector;
}

void ApplicationWindow::paintGL()
{
    eye = cameraPosition - target;

    rotateCamera();
    zoomCamera();
    panCamera();

    cameraPosition = target + eye;

    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt(cameraPosition, target, cameraUp);

    //************************************************

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

