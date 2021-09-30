#ifndef POINTCLOUDVIEWER_H
#define POINTCLOUDVIEWER_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>

#include <memory>

class QOpenGLShaderProgram;

namespace MHV
{
    class Memory;
}

namespace MHV
{
    class PointCloudViewer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
    {
        Q_OBJECT

        public:
            PointCloudViewer();
            ~PointCloudViewer() override;
        protected:
            void initializeGL() override;
            void resizeGL(int w, int h) override;
            void paintGL() override;
            void mouseMoveEvent(QMouseEvent *e) override;
            void mousePressEvent(QMouseEvent *e) override;
            void wheelEvent(QWheelEvent *e) override;
            void timerEvent(QTimerEvent* e) override;
        private:
            bool makePointCloud();
        private:
            QOpenGLBuffer _vbo;
            std::unique_ptr<QOpenGLShaderProgram> _program;

            std::unique_ptr<MHV::Memory> _utils;

            QMatrix4x4 _projectionMat;
            QMatrix4x4 _viewMat;
            QMatrix4x4 _modelMat;

            QPointF _mousePos;
    };
}

#endif // POINTCLOUDVIEWER_H
