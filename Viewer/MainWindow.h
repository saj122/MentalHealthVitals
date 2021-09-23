#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

        private slots:
            void on_actionExit_triggered();
            void depthViewerChecked(bool checked);
            void pointCloudViewerChecked(bool checked);

        private:
            Ui::MainWindow *ui;

            ImageViewer* _rgbViewer;
            ImageViewer* _depthViewer;
            PointCloudViewer* _pointCloudViewer;
    };
}

#endif // MAINWINDOW_H
