#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "ImageViewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Viewer");

    _imageViewer = new ImageViewer();
    ui->horizontalLayout->addWidget(_imageViewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

