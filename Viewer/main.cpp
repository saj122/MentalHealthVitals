#include "MainWindow.h"

#include <QApplication>
#include <QSurfaceFormat>

#include <stdio.h>

int main(int argc, char *argv[])
{
    QSurfaceFormat fmt;
    fmt.setRenderableType(QSurfaceFormat::OpenGL);
    fmt.setMajorVersion(3);
    fmt.setMinorVersion(2);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

    //system("../../start.sh");

    QApplication a(argc, argv);
    MHV::MainWindow w;
    w.show();
    return a.exec();
}
