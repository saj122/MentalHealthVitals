#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
class QOpenGLTexture;
QT_END_NAMESPACE

class DRUtils;

class ImageViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    public:
        enum class Type
        {
            RGB,
            DEPTH
        };
    public:
        ImageViewer(Type type = Type::RGB);
        ~ImageViewer();
    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
        void timerEvent(QTimerEvent* event);
    private:
        void makeImageTexture();
    private:
        QOpenGLBuffer _vbo;
        QOpenGLShaderProgram* _program;
        QOpenGLTexture* _texture;

        DRUtils* _utils;

        Type _viewerType;
};

#endif // IMAGEVIEWER_H
