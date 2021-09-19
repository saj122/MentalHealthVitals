#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageViewer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionExit_triggered();
        void depthViewerChecked(bool checked);

    private:
        Ui::MainWindow *ui;

        ImageViewer* _rgbViewer;
        ImageViewer* _depthViewer;
};
#endif // MAINWINDOW_H
