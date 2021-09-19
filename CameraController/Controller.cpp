#include "Controller.h"

#include "Astra.h"

#include <csignal>

volatile bool __stop;

void sigHandler(int s)
{
    __stop = true;
}

Controller::Controller() : _astra(nullptr)
{
    std::signal(SIGINT,  sigHandler);
}

Controller::~Controller()
{
    if(_astra)
        delete _astra;
}

void Controller::start()
{
    _astra = new Astra();
    _astra->init();

    while(!__stop)
    {
        _astra->run();
    }
}
