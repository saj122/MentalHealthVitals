#include "PointCloudViewer.h"

#include "Memory.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#define WIDTH 640
#define HEIGHT 480

MHV::PointCloudViewer::PointCloudViewer() : _utils(new Memory(WIDTH, HEIGHT))
{
    startTimer(10);

    qreal aspect = qreal(640) / qreal(480);

    const qreal zNear = 0.1, zFar = 15.0, fov = 45.0;

    _projection.perspective(fov, aspect, zNear, zFar);
}

MHV::PointCloudViewer::~PointCloudViewer()
{
    makeCurrent();
    _vbo.destroy();
    _texture->destroy();
    doneCurrent();
}

void MHV::PointCloudViewer::timerEvent(QTimerEvent* event)
{
    update();
}

void MHV::PointCloudViewer::initializeGL()
{
    initializeOpenGLFunctions();

    makePointCloud();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    std::unique_ptr<QOpenGLShader> vshader = std::make_unique<QOpenGLShader>(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 120\n"
        "attribute vec3 aPos;\n"
        "uniform mat4 mvp;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mvp*vec4(aPos, 1.0);\n"
        "    gl_PointSize = 50.0;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    std::unique_ptr<QOpenGLShader> fshader = std::make_unique<QOpenGLShader>(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "#version 120\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(0.0,0.0,1.0,1.0);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = std::make_unique<QOpenGLShaderProgram>();
    _program->addShader(vshader.get());
    _program->addShader(fshader.get());
    _program->bindAttributeLocation("aPos", 0);
    _program->link();
    _program->bind();

    QMatrix4x4 matrix;
    matrix.lookAt(QVector3D(0.0,0.0,-5.0), QVector3D(0.0,0.0,0.0), QVector3D(0.0,1.0,0.0));
    _program->setUniformValue("mvp", _projection*matrix);
}

void MHV::PointCloudViewer::paintGL()
{
    QColor clearColor = Qt::black;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   _program->enableAttributeArray(0);
   _program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3*sizeof(float));

   glDrawArrays(GL_POINTS, 0, 640*480);
}

void MHV::PointCloudViewer::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 0.1, zFar = 15.0, fov = 45.0;

    _projection.setToIdentity();

    _projection.perspective(fov, aspect, zNear, zFar);
}

void MHV::PointCloudViewer::makePointCloud()
{
    const float* points = _utils->getPointCloudData();

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(points, (int)(sizeof(points)/3*sizeof(float)));
}
