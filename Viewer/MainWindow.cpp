#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Config.h"

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

    MHV::Config::loadConfig();
    std::string type = MHV::Config::getType();

    if(type.compare("RGBD") == 0)
    {
        ui->actionDepth->setCheckable(true);
        ui->actionDepth->setChecked(false);
        ui->actionDepth->setShortcut(QKeySequence(QString::fromStdString("Ctrl+D")));
        ui->actionPoint_Cloud->setCheckable(true);
        ui->actionPoint_Cloud->setChecked(false);
        ui->actionPoint_Cloud->setShortcut(QKeySequence(QString::fromStdString("Ctrl+P")));

        connect(ui->actionDepth, SIGNAL(toggled(bool)), this, SLOT(depthViewerChecked(bool)));
        connect(ui->actionPoint_Cloud, SIGNAL(toggled(bool)), this, SLOT(pointCloudViewerChecked(bool)));

        _depthViewer = std::make_unique<MHV::ImageViewer>(MHV::ImageViewer::Type::DEPTH);
        _pointCloudViewer = std::make_unique<MHV::PointCloudViewer>();
    }
    else if(type.compare("RGB") == 0)
    {
        ui->actionDepth->setCheckable(false);
        ui->actionDepth->setChecked(false);
        ui->actionDepth->setVisible(false);
        ui->actionPoint_Cloud->setCheckable(false);
        ui->actionPoint_Cloud->setChecked(false);
        ui->actionPoint_Cloud->setVisible(false);
    }

    _rgbViewer = std::make_unique<MHV::ImageViewer>(MHV::ImageViewer::Type::RGB);

    ui->gridLayout->addWidget(_rgbViewer.get());
}

MHV::MainWindow::~MainWindow()
{
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
        ui->gridLayout->addWidget(_depthViewer.get(),1,0);
        _depthViewer->show();
    }
    else
    {
        if(_depthViewer)
        {
            _depthViewer->close();
            ui->gridLayout->removeWidget(_depthViewer.get());
        }
    }
}

void MHV::MainWindow::pointCloudViewerChecked(bool checked)
{
    if(checked)
    {
        ui->gridLayout->addWidget(_pointCloudViewer.get(),0,1,0,1);
        _pointCloudViewer->show();
    }
    else
    {
        if(_pointCloudViewer)
        {
            _pointCloudViewer->close();
            ui->gridLayout->removeWidget(_pointCloudViewer.get());
        }
    }
}
