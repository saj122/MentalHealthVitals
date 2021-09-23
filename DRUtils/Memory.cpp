#include "Memory.h"

#include <QSharedMemory>

#include <iostream>

MHV::Memory::Memory(int width, int height) : _colorSharedMemory(new QSharedMemory("DeviceRGB")),
                     _depthSharedMemory(new QSharedMemory("DeviceDepth")),
                     _pointCloudSharedMemory(new QSharedMemory("DevicePointCloud"))
{
    _rgbData = std::make_unique<unsigned char[]>(width*height*3);
    _depthData = std::make_unique<unsigned char[]>(width*height*2);
    _pointCloudData = std::make_unique<float[]>(width*height*3);
}

MHV::Memory::~Memory()
{
    if (_depthSharedMemory->isAttached())
    {
        _depthSharedMemory->detach();
    }

    if (_colorSharedMemory->isAttached())
    {
        _colorSharedMemory->detach();
    }

    if (_pointCloudSharedMemory->isAttached())
    {
        _pointCloudSharedMemory->detach();
    }
}

void MHV::Memory::setRGBData(const void* data, int size)
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

void MHV::Memory::setDepthData(const void* data, int size)
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

void MHV::Memory::setPointCloudData(const float* data, int size)
{
    if (_pointCloudSharedMemory->isAttached())
    {
        _pointCloudSharedMemory->detach();
    }

    if(!_pointCloudSharedMemory->create(size))
    {
        std::cout << "DRUtils.cpp - Unable to create shared point cloud memory segment." << std::endl;
        return;
    }

    _pointCloudSharedMemory->lock();
    void* to = _pointCloudSharedMemory->data();
    memcpy(to, data, qMin(_pointCloudSharedMemory->size(), size));
    _pointCloudSharedMemory->unlock();
}

const unsigned char* MHV::Memory::getRGBData()
{
    if(!_colorSharedMemory->attach())
    {
        std::cout << "DRUtils.cpp - Failed to attach to RGB shared memory." << std::endl;
    }

    _colorSharedMemory->lock();
    memcpy(_rgbData.get(), _colorSharedMemory->data(), _colorSharedMemory->size());
    _colorSharedMemory->unlock();

    _colorSharedMemory->detach();

    return _rgbData.get();
}

const unsigned char* MHV::Memory::getDepthData()
{
    if(!_depthSharedMemory->attach())
    {
        std::cout << "DRUtils.cpp - Failed to attach to depth shared memory." << std::endl;
    }

    _depthSharedMemory->lock();
    memcpy(_depthData.get(), _depthSharedMemory->data(), _depthSharedMemory->size());
    _depthSharedMemory->unlock();

    _depthSharedMemory->detach();

    return _depthData.get();
}

const float* MHV::Memory::getPointCloudData()
{
    if(!_pointCloudSharedMemory->attach())
    {
        std::cout << "DRUtils.cpp - Failed to attach to depth shared memory." << std::endl;
    }

    _pointCloudSharedMemory->lock();
    memcpy(_pointCloudData.get(), _pointCloudSharedMemory->data(), _pointCloudSharedMemory->size());
    _pointCloudSharedMemory->unlock();

    _pointCloudSharedMemory->detach();

    return _pointCloudData.get();
}
