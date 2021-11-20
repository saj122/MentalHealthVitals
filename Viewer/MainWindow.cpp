#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Config.h"
#include "Patient.h"
#include "Hashing.h"
#include "Database.h"

#include "ImageViewer.h"
#include "PointCloudViewer.h"

MHV::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _rgbViewer(nullptr)
    , _depthViewer(nullptr)
    , _pointCloudViewer(nullptr)
    , _database(nullptr)
    , _hashing(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Viewer");

    _database = std::make_unique<Database>();
    _hashing = std::make_unique<Hashing>();

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

        _depthViewer = std::make_unique<MHV::ImageViewer>(MHV::ImageViewer::Type::DEPTH);
        _pointCloudViewer = std::make_unique<MHV::PointCloudViewer>();

        connect(ui->actionDepth, SIGNAL(toggled(bool)), this, SLOT(depthViewerChecked(bool)));
        connect(ui->actionPoint_Cloud, SIGNAL(toggled(bool)), this, SLOT(pointCloudViewerChecked(bool)));
    }
    else if(type.compare("RGB") == 0)
    {
        ui->actionDepth->setCheckable(false);
        ui->actionDepth->setChecked(false);
        ui->actionPoint_Cloud->setCheckable(false);
        ui->actionPoint_Cloud->setChecked(false);
    }

    ui->stackedWidget->setCurrentIndex(0);

    _rgbViewer = std::make_unique<MHV::ImageViewer>(MHV::ImageViewer::Type::RGB);

    ui->viewersLayout->addWidget(_rgbViewer.get());

    ui->registerButton->setProperty("page", QVariant::fromValue(1));
    ui->backButtonRP->setProperty("page", QVariant::fromValue(0));
    ui->submitButtonRP->setProperty("page", QVariant::fromValue(0));
    ui->backLoginButton->setProperty("page", QVariant::fromValue(0));

    connect(ui->registerButton, SIGNAL(pressed()), this, SLOT(setToPage()));
    connect(ui->backButtonRP, SIGNAL(pressed()), this, SLOT(setToPage()));
    connect(ui->submitButtonRP, SIGNAL(pressed()), this, SLOT(registerUser()));
    connect(ui->loginButton, SIGNAL(pressed()), this, SLOT(loginUser()));
    connect(ui->backLoginButton, SIGNAL(pressed()), this, SLOT(setToPage()));
}

MHV::MainWindow::~MainWindow()
{
    delete ui;
}

void MHV::MainWindow::setToPage()
{
    ui->stackedWidget->setCurrentIndex(QObject::sender()->property("page").toInt());
}

void MHV::MainWindow::loginUser()
{
    QString userName = ui->usernameEdit->text();
    std::optional<std::string> res = _database->lookUpUser(userName.toStdString());
}

void MHV::MainWindow::registerUser()
{
    QString userName = ui->usernameRP->text();
    QString passWord = ui->passwordRP->text();
    std::optional<std::string> res = _database->lookUpUser(userName.toStdString());
    if(!res)
    {
        std::optional<std::pair<std::string,std::string>> hashPair = _hashing->encryptPassword(passWord.toStdString());

        Patient pat;
        pat.firstName = ui->firstNameRP->text().toStdString();
        pat.lastName = ui->lastNameRP->text().toStdString();
        pat.age = ui->ageRP->text().toStdString();
        pat.username = userName.toStdString();
        pat.password = passWord.toStdString();
        pat.email = ui->emailRP->text().toStdString();
        pat.areaCode = ui->areaCodeRP->text().toStdString();
        pat.phoneNumber = ui->phoneNumberRP->text().toStdString();
        pat.address = ui->addressRP->text().toStdString();
        pat.other = ui->extraAddressRP->text().toStdString();
        pat.city = ui->cityRP->text().toStdString();
        pat.state = ui->stateRP->text().toStdString();
        pat.zipCode = ui->zipCodeRP->text().toStdString();

        std::optional<std::string> res = _database->registerUser(pat);
        if(!res)
        {
            LOG(ERROR) << "Failed to register user.";
            return;
        }

        if(res)
        {
            if(!_database->registerPassword(res.value(), hashPair->second, hashPair->first))
            {
                LOG(ERROR) << "Failed to register password.";
                return;
            }
        }
    }
    else
    {
        LOG(INFO) << "User " << res.value() << " already exists";
    }

    ui->stackedWidget->setCurrentIndex(QObject::sender()->property("page").toInt());
}

void MHV::MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MHV::MainWindow::depthViewerChecked(bool checked)
{
    if(checked)
    {
        ui->viewersLayout->addWidget(_depthViewer.get(),1,0);
        _depthViewer->show();
    }
    else
    {
        if(_depthViewer)
        {
            _depthViewer->close();
            ui->viewersLayout->removeWidget(_depthViewer.get());
        }
    }
}

void MHV::MainWindow::pointCloudViewerChecked(bool checked)
{
    if(checked)
    {
        ui->viewersLayout->addWidget(_pointCloudViewer.get(),0,1,0,1);
        _pointCloudViewer->show();
    }
    else
    {
        if(_pointCloudViewer)
        {
            _pointCloudViewer->close();
            ui->viewersLayout->removeWidget(_pointCloudViewer.get());
        }
    }
}
