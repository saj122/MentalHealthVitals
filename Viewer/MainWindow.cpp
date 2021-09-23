#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "ImageViewer.h"
#include "PointCloudViewer.h"

MHV::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _rgbViewer(nullptr)
    , _depthViewer(nullptr)
    , _pointCloudViewer(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Viewer");

    ui->actionDepth->setCheckable(true);
    ui->actionDepth->setShortcut(QKeySequence(QString::fromStdString("Ctrl+D")));
    ui->actionPoint_Cloud->setCheckable(true);
    ui->actionPoint_Cloud->setShortcut(QKeySequence(QString::fromStdString("Ctrl+D")));

    connect(ui->actionDepth, SIGNAL(toggled(bool)), this, SLOT(depthViewerChecked(bool)));
    connect(ui->actionPoint_Cloud, SIGNAL(toggled(bool)), this, SLOT(pointCloudViewerChecked(bool)));

    _rgbViewer = new MHV::ImageViewer(MHV::ImageViewer::Type::RGB);
    ui->gridLayout->addWidget(_rgbViewer);
}

MHV::MainWindow::~MainWindow()
{
    if(_rgbViewer)
        _rgbViewer->close();
    if(_depthViewer)
        _depthViewer->close();
    delete ui;
}

void MHV::MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MHV::MainWindow::depthViewerChecked(bool checked)
{
    if(checked)
    {
        if(!_depthViewer)
            _depthViewer = new MHV::ImageViewer(MHV::ImageViewer::Type::DEPTH);
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

void MHV::MainWindow::pointCloudViewerChecked(bool checked)
{
    if(checked)
    {
        if(!_pointCloudViewer)
            _pointCloudViewer = new MHV::PointCloudViewer();
        ui->gridLayout->addWidget(_pointCloudViewer,0,1,0,1);
    }
    else
    {
        if(_pointCloudViewer)
        {
            _pointCloudViewer->close();
            ui->gridLayout->removeWidget(_pointCloudViewer);
        }
    }
}
