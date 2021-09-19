#include "ImageViewer.h"

#include "DRUtils.h"

#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include <iostream>

#include <OpenNI.h>

ImageViewer::ImageViewer() : _utils(new DRUtils())
{

}

ImageViewer::~ImageViewer()
{
    delete _utils;
    _vbo.destroy();
    delete _program;
}

void ImageViewer::initializeGL()
{
    initializeOpenGLFunctions();

    makeImageTexture();

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "#version 330 core\n"
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
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 textureCoords;\n"
    "uniform sampler2D texture;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture2D(texture, textureCoords);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = new QOpenGLShaderProgram;
    _program->addShader(vshader);
    _program->addShader(fshader);
    _program->bindAttributeLocation("vertex", 0);
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

   glBindTexture(GL_TEXTURE_2D, _textureId);
   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 640, 480, GL_RGB, GL_UNSIGNED_BYTE, _utils->getRGBData());

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ImageViewer::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side)/2, (h - side)/2, side, side);
}

void ImageViewer::makeImageTexture()
{
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, _utils->getRGBData());

    QVector<GLfloat> vertData;
    vertData.append(-1.0);
    vertData.append(-1.0);
    vertData.append(1.0);
    vertData.append(1.0);

    vertData.append(1.0);
    vertData.append(-1.0);
    vertData.append(0.0);
    vertData.append(1.0);

    vertData.append(-1.0);
    vertData.append(1.0);
    vertData.append(1.0);
    vertData.append(0.0);

    vertData.append(1.0);
    vertData.append(1.0);
    vertData.append(0.0);
    vertData.append(0.0);

    _vbo.create();
    _vbo.bind();
    _vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}
