#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui { class MainWindow; }

namespace MHV
{
    class ImageViewer;
    class PointCloudViewer;
}

namespace MHV
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow() override;

        private slots:
            void on_actionExit_triggered();
            void depthViewerChecked(bool checked);
            void pointCloudViewerChecked(bool checked);

        private:
            Ui::MainWindow *ui;

            std::unique_ptr<ImageViewer> _rgbViewer;
            std::unique_ptr<ImageViewer> _depthViewer;
            std::unique_ptr<PointCloudViewer> _pointCloudViewer;
    };
}

#endif // MAINWINDOW_H
