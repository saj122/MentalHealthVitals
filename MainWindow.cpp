#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QGridLayout>
#include <QThread>

#include "ImageViewer.h"
#include "Astra.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _camera(new Astra())
{
    ui->setupUi(this);

    try
    {
        _camera->init();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    _rgbViewer = new ImageViewer(ImageViewer::Type::RGB);
    ui->gridLayout->addWidget(_rgbViewer);

    _cameraThread = new QThread;
    _camera->moveToThread(_cameraThread);
    connect(_camera, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(_cameraThread, SIGNAL(started()), _camera, SLOT(process()));
    connect(_camera, SIGNAL(finished()), _cameraThread, SLOT(quit()));
    connect(_camera, SIGNAL(finished()), _camera, SLOT(deleteLater()));
    connect(_cameraThread, SIGNAL(finished()), _cameraThread, SLOT(deleteLater()));
    _cameraThread->start();
}

MainWindow::~MainWindow()
{
    _cameraThread->exit();
    delete _camera;
    delete _rgbViewer;
    delete ui;
}
