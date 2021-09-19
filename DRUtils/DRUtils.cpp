#include "DRUtils.h"

#include <QSharedMemory>

#include <iostream>

DRUtils::DRUtils() : _colorSharedMemory(new QSharedMemory("DeviceRGB")),
                     _depthSharedMemory(new QSharedMemory("DeviceDepth")),
                     _rgbData(new unsigned char[640*480*3]),
                     _depthData(new unsigned char[640*480])
{

}

DRUtils::~DRUtils()
{
    if (_depthSharedMemory->isAttached())
    {
        _depthSharedMemory->detach();
    }

    if (_colorSharedMemory->isAttached())
    {
        _colorSharedMemory->detach();
    }

    delete _colorSharedMemory;
    delete _depthSharedMemory;

    delete[] _rgbData;
    delete[] _depthData;
}

void DRUtils::setRGBData(const void* data, int size)
{
    if (_colorSharedMemory->isAttached())
    {
        _colorSharedMemory->detach();
    }

    if(!_colorSharedMemory->create(size))
    {
        std::cout << "DRUtils.cpp - Unable to create shared color memory segment." << std::endl;
        return;
    }

    _colorSharedMemory->lock();
    void* to = _colorSharedMemory->data();
    memcpy(to, data, qMin(_colorSharedMemory->size(), size));
    _colorSharedMemory->unlock();
}

void DRUtils::setDepthData(const void* data, int size)
{
    if (_depthSharedMemory->isAttached())
    {
        _depthSharedMemory->detach();
    }

    if(!_depthSharedMemory->create(size))
    {
        std::cout << "DRUtils.cpp - Unable to create shared depth memory segment." << std::endl;
        return;
    }

    _depthSharedMemory->lock();
    void* to = _depthSharedMemory->data();
    memcpy(to, data, qMin(_depthSharedMemory->size(), size));
    _depthSharedMemory->unlock();
}

const unsigned char* DRUtils::getRGBData()
{
    if(!_colorSharedMemory->attach())
    {
        std::cout << "DRUtils.cpp - Failed to attach to RGB shared memory." << std::endl;
    }

    _colorSharedMemory->lock();
    memcpy(_rgbData, _colorSharedMemory->data(), _colorSharedMemory->size());
    _colorSharedMemory->unlock();

    _colorSharedMemory->detach();

    return _rgbData;
}

const unsigned char* DRUtils::getDepthData()
{
    if(!_depthSharedMemory->attach())
    {
        std::cout << "DRUtils.cpp - Failed to attach to depth shared memory." << std::endl;
    }

    _depthSharedMemory->lock();
    memcpy(_depthData, _depthSharedMemory->data(), _depthSharedMemory->size());
    _depthSharedMemory->unlock();

    _depthSharedMemory->detach();

    return _depthData;
}
