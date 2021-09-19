#include "DRUtils.h"

#include <QBuffer>

#include <stdexcept>
#include <iostream>

DRUtils::DRUtils() : _colorSharedMemory("DeviceRGB"), _depthSharedMemory("DeviceDepth")
{

}

DRUtils::~DRUtils()
{
    if (_depthSharedMemory.isAttached())
    {
        _depthSharedMemory.detach();
    }

    if (_colorSharedMemory.isAttached())
    {
        _colorSharedMemory.detach();
    }
}

void DRUtils::setRGBData(const void* data, int size)
{
    if (_colorSharedMemory.isAttached())
    {
        _colorSharedMemory.detach();
    }

    if(!_colorSharedMemory.create(size))
    {
        std::runtime_error("DRUtils.cpp - Unable to create shared color memory segment.");
        return;
    }

    _colorSharedMemory.lock();
    void* to = _colorSharedMemory.data();
    memcpy(to, data, qMin(_colorSharedMemory.size(), size));
    _colorSharedMemory.unlock();
}

void DRUtils::setDepthData(const void* data, int size)
{
    if (_depthSharedMemory.isAttached())
    {
        _depthSharedMemory.detach();
    }

    if(!_depthSharedMemory.create(size))
    {
        std::runtime_error("DRUtils.cpp - Unable to create shared depth memory segment.");
        return;
    }

    _depthSharedMemory.lock();
    void* to = _depthSharedMemory.data();
    memcpy(to, data, qMin(_depthSharedMemory.size(), size));
    _depthSharedMemory.unlock();
}

const void* DRUtils::getRGBData()
{
    if(!_colorSharedMemory.attach())
    {
        std::runtime_error("DRUtils.cpp - Failed to attach to RGB shared memory.");
    }

    _colorSharedMemory.lock();
    const void* data = _colorSharedMemory.constData();
    _colorSharedMemory.unlock();

    return data;
}

const void* DRUtils::getDepthData()
{
    if(!_depthSharedMemory.attach())
    {
        std::runtime_error("DRUtils.cpp - Failed to attach to depth shared memory.");
    }

    _depthSharedMemory.lock();
    const void* data = _depthSharedMemory.constData();
    _depthSharedMemory.unlock();

    return data;
}
