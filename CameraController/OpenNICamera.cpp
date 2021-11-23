#include "OpenNICamera.h"

#include "MemoryFactory.h"

#include <glog/logging.h>

#include <math.h>

MHV::OpenNICamera::OpenNICamera(int width, int height) : _width(width),
                                                         _height(height),
                                                         _streams(new openni::VideoStream*[2]())
{
    _utils = MemoryFactory::create(width*height*3);
}

MHV::OpenNICamera::~OpenNICamera()
{
    if(_color.isValid())
        _color.destroy();

    openni::OpenNI::shutdown();
}

void MHV::OpenNICamera::init()
{
    openni::Status rc = openni::Status::STATUS_OK;

    rc = openni::OpenNI::initialize();
    if(rc != openni::Status::STATUS_OK)
    {
        openni::OpenNI::shutdown();
        LOG(FATAL) << "Failed to initialize device.";
    }

    rc = _device.open(openni::ANY_DEVICE);
    if(rc != openni::Status::STATUS_OK)
    {
        openni::OpenNI::shutdown();
        LOG(FATAL) << "Failed to open device.";
    }

    _device.setImageRegistrationMode(openni::ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    rc = _color.create(_device, openni::SENSOR_COLOR);
    if(rc == openni::Status::STATUS_OK)
    {
        rc = _color.start();
        if(rc != openni::STATUS_OK)
        {
            _color.destroy();
            openni::OpenNI::shutdown();
            LOG(FATAL) << "Failed to start color stream.";
        }
    }
    else
    {
        openni::OpenNI::shutdown();
        LOG(FATAL) << "Failed to create color video stream.";
    }

    if (!_color.isValid())
    {
        openni::OpenNI::shutdown();
        LOG(FATAL) << "No valid streams.";
    }

    _colorVideoMode = _color.getVideoMode();

    _colorVideoMode.setPixelFormat(openni::PixelFormat::PIXEL_FORMAT_RGB888);
    _colorVideoMode.setFps(30);
    _colorVideoMode.setResolution(_width, _height);

    _color.setVideoMode(_colorVideoMode);

    LOG(INFO) << "FPS: " << _colorVideoMode.getFps();

    _streams.get()[0] = &_color;
}

void MHV::OpenNICamera::run()
{
    if(isValid())
    {
        int changedIndex;
        openni::Status rc = openni::OpenNI::waitForAnyStream(_streams.get(), 2, &changedIndex);

        if (rc != openni::STATUS_OK)
        {
            LOG(ERROR) << "Wait for streams failed.";
        }

        _color.readFrame(&_colorFrame);
        if(_colorFrame.isValid())
        {
            _utils->setRGBData(_colorFrame.getData());
        }
    }
}

bool MHV::OpenNICamera::isValid()
{
    return _device.isValid();
}
