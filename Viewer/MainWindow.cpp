#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "ImageViewer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _rgbViewer(nullptr)
    , _depthViewer(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Viewer");

    ui->actionDepth->setCheckable(true);
    ui->actionDepth->setShortcut(QKeySequence(QString::fromStdString("Ctrl+D")));

    connect(ui->actionDepth, SIGNAL(toggled(bool)), this, SLOT(depthViewerChecked(bool)));

    _rgbViewer = new ImageViewer(ImageViewer::Type::RGB);
    ui->gridLayout->addWidget(_rgbViewer);
}

MainWindow::~MainWindow()
{
    if(_rgbViewer)
        _rgbViewer->close();
    if(_depthViewer)
        _depthViewer->close();
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::depthViewerChecked(bool checked)
{
    if(checked)
    {
        if(!_depthViewer)
            _depthViewer = new ImageViewer(ImageViewer::Type::DEPTH);
        ui->gridLayout->addWidget(_depthViewer,1,0);
    }
    else
    {
        if(_depthViewer)
        {
            _depthViewer->close();
            ui->gridLayout->removeWidget(_depthViewer);
        }
    }
}
