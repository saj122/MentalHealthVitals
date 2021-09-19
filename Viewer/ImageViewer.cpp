#include "ImageViewer.h"

#include "DRUtils.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <iostream>

#include <OpenNI.h>

ImageViewer::ImageViewer(Type type) : _utils(new DRUtils()), _viewerType(type)
{
    startTimer(32);
}

ImageViewer::~ImageViewer()
{
    delete _utils;
    _vbo.destroy();
    delete _program;
    delete _texture;
}

void ImageViewer::timerEvent(QTimerEvent* event)
{
    update();
}

void ImageViewer::initializeGL()
{
    initializeOpenGLFunctions();

    makeImageTexture();

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 120\n"
        "attribute vec2 aPos;\n"
        "attribute vec2 aTexCoord;\n"
        "varying vec2 textureCoords;\n"
        "void main()\n"
        "{\n"
        "    textureCoords = aTexCoord;\n"
        "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "#version 120\n"
        "varying vec2 textureCoords;\n"
        "uniform sampler2D texture;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, textureCoords);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = new QOpenGLShaderProgram;
    _program->addShader(vshader);
    _program->addShader(fshader);
    _program->bindAttributeLocation("aPos", 0);
    _program->bindAttributeLocation("aTexCoord", 1);
    _program->link();

    _program->bind();
    _program->setUniformValue("texture", 0);
}

void ImageViewer::paintGL()
{
    QColor clearColor = Qt::white;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   _program->enableAttributeArray(0);
   _program->enableAttributeArray(1);
   _program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4*sizeof(GLfloat));
   _program->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 2, 4*sizeof(GLfloat));

   if(_texture)
   {
       if(_viewerType == Type::RGB)
       {
           _texture->setData(QImage(_utils->getRGBData(), 640, 480, QImage::Format::Format_RGB888));
       }
       else if(_viewerType == Type::DEPTH)
       {
           _texture->setData(QImage(_utils->getDepthData(), 640, 480,QImage::Format::Format_Grayscale16));
       }
       _texture->bind();
   }
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ImageViewer::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side)/2, (h - side)/2, side, side);
}

void ImageViewer::makeImageTexture()
{
    if(_viewerType == Type::RGB)
    {
        _texture = new QOpenGLTexture(QImage(_utils->getRGBData(), 640, 480, QImage::Format::Format_RGB888));
    }
    else if(_viewerType == Type::DEPTH)
    {
        _texture = new QOpenGLTexture(QImage(_utils->getDepthData(), 640, 480, QImage::Format::Format_Grayscale16));
    }

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
    _vbo.allocate(vertData.constData(), (int)(vertData.count() * sizeof(GLfloat)));
}
