#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QThread;
QT_END_NAMESPACE

class Astra;
class ImageViewer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void errorString(QString string);

    private:
        Ui::MainWindow *ui;

        ImageViewer* _rgbViewer;

        Astra* _camera;

        QThread* _cameraThread;
};
#endif // MAINWINDOW_H
