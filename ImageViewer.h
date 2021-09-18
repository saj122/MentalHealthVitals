#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE

class ImageViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
    public:
        enum class Type
        {
            RGB,
            DEPTH
        };

    public:
        ImageViewer(Type type);
        ~ImageViewer();
    protected:
        void initializeGL() override;
        void resizeGL(int w, int h) override;
        void paintGL() override;
    private:
        void makeImageTexture();
    private:
        QOpenGLShaderProgram* _program;
        QOpenGLBuffer _vbo;

        GLuint _textureId;

        int _width;
        int _height;

        Type _viewerType;
};

#endif // IMAGEVIEWER_H
