#include "ImageViewer.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QSurfaceFormat>

#include <iostream>

#include <OpenNI.h>

ImageViewer::ImageViewer(Type type) : _viewerType(type)
{
    QSurfaceFormat fmt = QSurfaceFormat::defaultFormat();
    fmt.setVersion(3,3);
    fmt.setProfile(QSurfaceFormat::NoProfile);
    setFormat(fmt);
}

ImageViewer::~ImageViewer()
{
    _vbo.destroy();
    delete _program;
}

void ImageViewer::initializeGL()
{
    initializeOpenGLFunctions();

    QVector<GLfloat> vertData;
    vertData.append(-1.0);
    vertData.append(-1.0);
    vertData.append(0.0);
    vertData.append(0.0);

    vertData.append(1.0);
    vertData.append(-1.0);
    vertData.append(1.0);
    vertData.append(0.0);

    vertData.append(-1.0);
    vertData.append(1.0);
    vertData.append(0.0);
    vertData.append(1.0);

    vertData.append(1.0);
    vertData.append(1.0);
    vertData.append(1.0);
    vertData.append(1.0);

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 330\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 textureCoords;\n"
        "void main()\n"
        "{\n"
        "    textureCoords = aTexCoord;\n"
        "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "#version 330\n"
        "out vec4 FragColor;\n"
        "in vec2 textureCoords;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = new QOpenGLShaderProgram;
    _program->addShader(vshader);
    _program->addShader(fshader);
    _program->bindAttributeLocation("aPos", 0);
    _program->bindAttributeLocation("aTexCoord", 1);
    _program->link();

    _program->bind();
}

void ImageViewer::paintGL()
{
    QColor clearColor = Qt::blue;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _program->enableAttributeArray(0);
    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4*sizeof(GLfloat));
    _program->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 2, 4*sizeof(GLfloat));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ImageViewer::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side)/2, (h - side)/2, side, side);
}
