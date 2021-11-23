#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "Config.h"
#include "Patient.h"
#include "Hashing.h"
#include "Database.h"

#include "ImageViewer.h"

MHV::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _rgbViewer(nullptr)
    , _database(nullptr)
    , _hashing(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Viewer");

    _database = std::make_unique<Database>();
    _hashing = std::make_unique<Hashing>();

    MHV::Config::loadConfig();
    std::string type = MHV::Config::getType();

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
