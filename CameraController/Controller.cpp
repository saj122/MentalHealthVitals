#include "Controller.h"

#include "OpenNICamera.h"

#include <csignal>

volatile bool __stop;

void sigHandler(int s)
{
    __stop = true;
}

MHV::Controller::Controller() : _openNICamera(nullptr)
{
    __stop = false;
    std::signal(SIGINT,  sigHandler);
}

MHV::Controller::~Controller()
{
    if(_openNICamera)
        delete _openNICamera;
}

void MHV::Controller::start()
{
    _openNICamera = new MHV::OpenNICamera();
    _openNICamera->init();

    while(!__stop || _openNICamera->isValid())
    {
        _openNICamera->run();
    }
}
