#include "OpenNICamera.h"

#include <stdexcept>
#include <iostream>

#include <DRUtils.h>

OpenNICamera::OpenNICamera() : _utils(new DRUtils())
{
}

OpenNICamera::~OpenNICamera()
{
    if(_device.isValid())
        _device.close();

    if(_depth.isValid())
        _depth.destroy();

    if(_color.isValid())
        _color.destroy();

    if(_streams)
        delete [] _streams;

    delete _utils;

    openni::OpenNI::shutdown();
}

void OpenNICamera::init()
{
    openni::Status rc = openni::Status::STATUS_OK;

    rc = openni::OpenNI::initialize();
    if(rc != openni::Status::STATUS_OK)
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error("OpenNICamera.cpp - Failed to initialize OpenNI.");
    }

    rc = _device.open(openni::ANY_DEVICE);
    if(rc != openni::Status::STATUS_OK)
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error("OpenNICamera.cpp - Failed to open device.");
    }

    _device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_OFF);

    rc = _depth.create(_device, openni::SENSOR_DEPTH);
    if(rc == openni::Status::STATUS_OK)
    {
        rc = _depth.start();
        if(rc != openni::STATUS_OK)
        {
            _depth.destroy();
            openni::OpenNI::shutdown();
            throw std::runtime_error("OpenNICamera.cpp - Failed to start depth stream.");
        }
    }
    else
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error("OpenNICamera.cpp - Failed to create depth video stream.");
    }

    rc = _color.create(_device, openni::SENSOR_COLOR);
    if(rc == openni::Status::STATUS_OK)
    {
        rc = _color.start();
        if(rc != openni::STATUS_OK)
        {
            _color.destroy();
            openni::OpenNI::shutdown();
            throw std::runtime_error("OpenNICamera.cpp - Failed to start color stream.");
        }
    }
    else
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error("OpenNICamera.cpp - Failed to create color video stream.");
    }

    if (!_depth.isValid() && !_color.isValid())
    {
        openni::OpenNI::shutdown();
        throw std::runtime_error("OpenNICamera.cpp - No valid streams.");
    }

    _depthVideoMode = _depth.getVideoMode();
    _colorVideoMode = _color.getVideoMode();

    _colorVideoMode.setPixelFormat(openni::PixelFormat::PIXEL_FORMAT_RGB888);
    _depthVideoMode.setPixelFormat(openni::PixelFormat::PIXEL_FORMAT_GRAY8);
    _colorVideoMode.setFps(30);
    _depthVideoMode.setFps(30);
    _colorVideoMode.setResolution(640,480);
    _depthVideoMode.setResolution(640,480);

    _depth.setVideoMode(_depthVideoMode);
    _color.setVideoMode(_colorVideoMode);

    int depthWidth = _depthVideoMode.getResolutionX();
    int depthHeight = _depthVideoMode.getResolutionY();
    int colorWidth = _colorVideoMode.getResolutionX();
    int colorHeight = _colorVideoMode.getResolutionY();

    if(depthWidth == colorWidth && depthHeight == colorHeight)
    {
        _width = depthWidth;
        _height = depthHeight;
    }
    else
    {
        std::runtime_error("Astra.cpp - Depth and color resolution are not the same.");
    }

    std::cout << "Astra resolution X: " << _width << std::endl;
    std::cout << "Astra resolution Y: " << _height << std::endl;
    std::cout << "Astra FPS: " << _colorVideoMode.getFps() << std::endl;

    _streams = new openni::VideoStream*[2];

    _streams[0] = &_depth;
    _streams[1] = &_color;
}

void OpenNICamera::run()
{
    int changedIndex;
    openni::Status rc = openni::OpenNI::waitForAnyStream(_streams, 2, &changedIndex);

    if (rc != openni::STATUS_OK)
    {
        std::runtime_error("OpenNICamera.cpp - Wait for streams failed.");
    }

    _depth.readFrame(&_depthFrame);
    if(_depthFrame.isValid())
    {
        _utils->setDepthData(_depthFrame.getData(), _depthFrame.getDataSize());
    }

    _color.readFrame(&_colorFrame);
    if(_colorFrame.isValid())
    {
        _utils->setRGBData(_colorFrame.getData(), _colorFrame.getDataSize());
    }
}
