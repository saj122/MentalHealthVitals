#include "Controller.h"

#include "OpenNICamera.h"

#include <csignal>

volatile bool __stop;

void sigHandler(int s)
{
    __stop = true;
}

Controller::Controller() : _openNICamera(nullptr)
{
    __stop = false;
    std::signal(SIGINT,  sigHandler);
}

Controller::~Controller()
{
    if(_openNICamera)
        delete _openNICamera;
}

void Controller::start()
{
    _openNICamera = new OpenNICamera();
    _openNICamera->init();

    while(!__stop)
    {
        _openNICamera->run();
    }
}
