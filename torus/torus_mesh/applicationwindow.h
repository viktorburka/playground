#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_3_Core>
#include <QMatrix4x4>
#include <QVector2D>

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
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    enum State { NONE = -1, ROTATE = 0, ZOOM = 1, PAN = 2, TOUCH_ROTATE = 3, TOUCH_ZOOM_PAN = 4 };

    void zoomCamera();
    void rotateCamera();
    void panCamera();
    State mouseButtonToState(Qt::MouseButton button) const;
    QVector2D getMouseOnCircle(int pageX, int pageY) const;
    QVector2D getMouseOnScreen(int pageX, int pageY) const;

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

    QVector2D                zoomStart;
    QVector2D                zoomEnd;
    QVector2D                moveCurr;
    QVector2D                movePrev;
    QVector2D                panStart;
    QVector2D                panEnd;
    QVector3D                eye;
    QVector3D                target;
    QVector3D                cameraPosition{0.0, 0.0, 3.0};
    QVector3D                cameraUp{0.0,1.0,0.0};
    QVector3D                lastAxis;
    double                   zoomSpeed{1.1};
    double                   rotateSpeed{100.0};
    double                   panSpeed{0.3};
    double                   dynamicDampingFactor{0.3};
    double                   lastAngle{0.0};
    bool                     staticMoving{true};
    State                    state{State::NONE};
    State                    prevState{State::NONE};
};

#endif // APPLICATIONWINDOW_H
