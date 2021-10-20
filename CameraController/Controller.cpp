#include "Controller.h"

#include "OpenNICamera.h"
#include "GSCamera.h"
#include "Config.h"

#include <csignal>
#include <string>

#include <glog/logging.h>

volatile bool __stop;

void sigHandler(int s)
{
    __stop = true;
}

MHV::Controller::Controller() : _camera(nullptr)
{
    __stop = false;
    std::signal(SIGINT,  sigHandler);
    std::signal(SIGTERM, sigHandler);

    MHV::Config::loadConfig();
}

MHV::Controller::~Controller()
{

}

void MHV::Controller::start()
{
    std::string source = MHV::Config::getSource();
    int w = MHV::Config::getWidth();
    int h = MHV::Config::getHeight();

    LOG(INFO) << "Source of camera: " << source;
    LOG(INFO) << "Width of image: " << w;
    LOG(INFO) << "Height of image: " << h;

    if(source.compare("OpenNI") == 0)
        _camera = std::make_unique<MHV::OpenNICamera>(w,h);
    else if(source.compare("V4L") == 0 || source.compare("AVFoundation") == 0)
        _camera = std::make_unique<MHV::GSCamera>(w,h);

    _camera->init();

    LOG(INFO) << "Camera initialized and starting.";

    while(!__stop)
    {
        _camera->run();
    }
}
