#include "ImageViewer.h"

#include <QOpenGLShader>
#include <QOpenGLTexture>

#include "MemoryFactory.h"

#define WIDTH 640
#define HEIGHT 480

MHV::ImageViewer::ImageViewer(Type type) : _viewerType(type)
{
    _utils = MemoryFactory::create(WIDTH*HEIGHT*3);
    startTimer(1);
}

MHV::ImageViewer::~ImageViewer()
{
    makeCurrent();
    _vbo.destroy();
    if(_texture)
        _texture->destroy();
    doneCurrent();
}

void MHV::ImageViewer::timerEvent(QTimerEvent* event)
{
    update();
}

void MHV::ImageViewer::initializeGL()
{
    initializeOpenGLFunctions();

    makeImageTexture();

    std::unique_ptr<QOpenGLShader> vshader = std::make_unique<QOpenGLShader>(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute vec2 aPos;\n"
        "attribute vec2 aTexCoord;\n"
        "varying vec2 textureCoords;\n"
        "void main()\n"
        "{\n"
        "    textureCoords = aTexCoord;\n"
        "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    std::unique_ptr<QOpenGLShader> fshader = std::make_unique<QOpenGLShader>(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "varying vec2 textureCoords;\n"
        "uniform sampler2D texture;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, textureCoords);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    _program = std::make_unique<QOpenGLShaderProgram>();
    _program->addShader(vshader.get());
    _program->addShader(fshader.get());
    _program->bindAttributeLocation("aPos", 0);
    _program->bindAttributeLocation("aTexCoord", 1);
    _program->link();

    _program->bind();
    _program->setUniformValue("texture", 0);
}

void MHV::ImageViewer::paintGL()
{
    QColor clearColor = Qt::black;
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT);

   _program->enableAttributeArray(0);
   _program->enableAttributeArray(1);
   _program->setAttributeBuffer(0, GL_FLOAT, 0, 2, 4*sizeof(GLfloat));
   _program->setAttributeBuffer(1, GL_FLOAT, 2*sizeof(GLfloat), 2, 4*sizeof(GLfloat));

   if(_texture)
   {
       if(_viewerType == Type::RGB)
       {
           const unsigned char* image = _utils->getRGBData();
           if(image)
               _texture->setData(QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::PixelType::UInt8, image);
       }
       else if(_viewerType == Type::DEPTH)
       {
           const unsigned char* image = _utils->getDepthData();
           if (image)
               _texture->setData(QOpenGLTexture::PixelFormat::Luminance, QOpenGLTexture::PixelType::UInt16, image);
       }
       _texture->bind();
   }
   else
   {
       makeImageTexture();
   }
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void MHV::ImageViewer::resizeGL(int w, int h)
{
    int side = qMin(w, h);
    glViewport((w - side)/2, (h - side)/2, side, side);
}

void MHV::ImageViewer::makeImageTexture()
{
    if(_viewerType == Type::RGB)
    {
        const unsigned char* image = _utils->getRGBData();
        if (image)
            _texture = std::make_unique<QOpenGLTexture>(QImage(image, 640, 480, QImage::Format::Format_RGB888).mirrored(false,true),  QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps);
    }
    else if(_viewerType == Type::DEPTH)
    {
        const unsigned char* image = _utils->getDepthData();
        if (image)
            _texture = std::make_unique<QOpenGLTexture>(QImage(image, 640, 480, QImage::Format::Format_Grayscale16).mirrored(false,true),  QOpenGLTexture::MipMapGeneration::DontGenerateMipMaps);
    }

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
    _vbo.allocate(vertData.constData(), (int)(vertData.count() * sizeof(GLfloat)));
}
