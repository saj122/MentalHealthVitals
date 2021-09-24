#include "PointCloudViewer.h"

#include "Memory.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QVector>

#include <utility>
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

MHV::PointCloudViewer::PointCloudViewer() : _utils(new Memory(WIDTH, HEIGHT))
{
    startTimer(30);

    _viewMat.lookAt(QVector3D(0.0,0.0,0.0), QVector3D(0.0,0.0,10.0),QVector3D(0.0,1.0,0.0));
}

MHV::PointCloudViewer::~PointCloudViewer()
{
    makeCurrent();
    _vbo.destroy();
    doneCurrent();
}

void MHV::PointCloudViewer::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::MiddleButton)
    {

    }
}

void MHV::PointCloudViewer::timerEvent(QTimerEvent* event)
{
    update();
}

void MHV::PointCloudViewer::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_PROGRAM_POINT_SIZE);

    QOpenGLShader* vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 vp;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vp*vec4(aPos, 1.0);\n"
        "    gl_PointSize = 1.0;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader* fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.0,0.0,1.0,1.0);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = std::make_unique<QOpenGLShaderProgram>();
    _program->addShader(vshader);
    _program->addShader(fshader);
    _program->bindAttributeLocation("aPos", 0);
    _program->link();
    _program->bind();
}

void MHV::PointCloudViewer::paintGL()
{
    makePointCloud();
    QColor clearColor = Qt::black;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   _program->enableAttributeArray(0);
   _program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3*sizeof(GLfloat));

   _program->setUniformValue("vp", _projectionMat * _viewMat);

   glDrawArrays(GL_POINTS, 0, WIDTH*HEIGHT);
}

void MHV::PointCloudViewer::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 0.001, zFar = 50000.0, fov = 10.0;

    _projectionMat.setToIdentity();

    _projectionMat.perspective(fov, aspect, zNear, zFar);
}

void MHV::PointCloudViewer::makePointCloud()
{
    const float* points = _utils->getPointCloudData();

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(points, WIDTH*HEIGHT*3*sizeof(float));
}
