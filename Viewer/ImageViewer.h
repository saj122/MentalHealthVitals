#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE

class DRUtils;

class ImageViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    public:
        ImageViewer();
        ~ImageViewer();
    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
    private:
        void makeImageTexture();
    private:
        QOpenGLBuffer _vbo;
        QOpenGLShaderProgram* _program;

        GLuint _textureId;

        DRUtils* _utils;
};

#endif // IMAGEVIEWER_H
