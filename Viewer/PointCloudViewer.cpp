#include "PointCloudViewer.h"

#include "MemoryFactory.h"

#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QVector>

#define WIDTH 640
#define HEIGHT 480

MHV::PointCloudViewer::PointCloudViewer() : _mousePos(0.0,0.0)
{
    _utils = MemoryFactory::create(WIDTH*HEIGHT*3,WIDTH*HEIGHT*2,WIDTH*HEIGHT*3*sizeof(float));

    startTimer(33);
    _modelMat.setToIdentity();

    _viewMat.lookAt(QVector3D(0.0,0.0,10000.0), QVector3D(0.0,0.0,20000.0), QVector3D(0.0,1.0,0.0));

    _projectionMat.setToIdentity();

    _projectionMat.perspective(_fov, WIDTH/HEIGHT, _zNear, _zFar);
}

MHV::PointCloudViewer::~PointCloudViewer()
{
    makeCurrent();
    _vao.destroy();
    _vbo.destroy();
    doneCurrent();
}

void MHV::PointCloudViewer::timerEvent(QTimerEvent* e)
{
    update();
}

void MHV::PointCloudViewer::mousePressEvent(QMouseEvent *e)
{
    _mousePos = e->position();
}

void MHV::PointCloudViewer::wheelEvent(QWheelEvent *e)
{

}

void MHV::PointCloudViewer::mouseMoveEvent(QMouseEvent *e)
{
    _mousePos = e->position();
}

void MHV::PointCloudViewer::initializeGL()
{
    initializeOpenGLFunctions();

    makePointCloud();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_PROGRAM_POINT_SIZE);

    auto vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 150 core\n"
        "in vec3 aPos;\n"
        "uniform mat4 mv;\n"
        "uniform mat4 p;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = p*mv*vec4(aPos, 1.0);\n"
        "    gl_PointSize = 1.0;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    auto fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "#version 150 core\n"
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

    _vao.create();
    _vao.bind();
}

void MHV::PointCloudViewer::paintGL()
{
    QColor clearColor = Qt::black;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    makePointCloud();

    _program->enableAttributeArray(0);
    _program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 3*sizeof(GLfloat));

    _program->setUniformValue("mv", _viewMat * _modelMat);
    _program->setUniformValue("p", _projectionMat);

    glDrawArrays(GL_POINTS, 0, WIDTH*HEIGHT);
}

void MHV::PointCloudViewer::resizeGL(int w, int h)
{
    auto aspect = (float)(w / h ? h : 1);

    _projectionMat.setToIdentity();

    _projectionMat.perspective(_fov, aspect, _zNear, _zFar);
}

bool MHV::PointCloudViewer::makePointCloud()
{
    const float* points = _utils->getPointCloudData();
    if (points)
    {
        _vbo.create();
        _vbo.bind();
        _vbo.allocate(points, WIDTH * HEIGHT * 3 * sizeof(float));
        return true;
    }

    return false;
}
