#ifndef POINTCLOUDVIEWER_H
#define POINTCLOUDVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

#include <memory>

class QOpenGLShaderProgram;
class QOpenGLTexture;

namespace MHV
{
    class Memory;
}

namespace MHV
{
    class PointCloudViewer : public QOpenGLWidget, protected QOpenGLFunctions
    {
        public:
            PointCloudViewer();
            ~PointCloudViewer();
        protected:
            void initializeGL() override;
            void resizeGL(int w, int h) override;
            void paintGL() override;
            void timerEvent(QTimerEvent* event) override;
        private:
            void makePointCloud();
        private:
            QOpenGLBuffer _vbo;
            std::unique_ptr<QOpenGLShaderProgram> _program;
            std::unique_ptr<QOpenGLTexture> _texture;

            std::unique_ptr<MHV::Memory> _utils;

            QMatrix4x4 _projection;
    };
}

#endif // POINTCLOUDVIEWER_H