#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

#include <memory>

class QOpenGLShaderProgram;
class QOpenGLTexture;

namespace MHV
{
    class Memory;
}

namespace MHV
{
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
            void timerEvent(QTimerEvent* event) override;
        private:
            void makeImageTexture();
        private:
            QOpenGLVertexArrayObject _vao;
            QOpenGLBuffer _vbo;
            std::unique_ptr<QOpenGLShaderProgram> _program;
            std::unique_ptr<QOpenGLTexture> _texture;

            std::unique_ptr<MHV::Memory> _utils;

            Type _viewerType;
    };
}

#endif // IMAGEVIEWER_H
