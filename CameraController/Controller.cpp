#include "Controller.h"

#include "OpenNICamera.h"

#include <csignal>

#include <glog/logging.h>

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

}

void MHV::Controller::start()
{
    _openNICamera = std::make_unique<MHV::OpenNICamera>();
    _openNICamera->init();

    LOG(INFO) << "Camera initialized and starting.";

    while(!__stop && _openNICamera->isValid())
    {
        _openNICamera->run();
    }
}
