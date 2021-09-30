#include "OpenNICamera.h"

#include "MemoryFactory.h"

#include <glog/logging.h>

#include <math.h>

#define WIDTH 640
#define HEIGHT 480

MHV::OpenNICamera::OpenNICamera() : _width(WIDTH),
                                    _height(HEIGHT),
                                    _streams(new openni::VideoStream*[2]())
{
    _utils = MemoryFactory::create();
}

MHV::OpenNICamera::~OpenNICamera()
{
    if(_device.isValid())
        _device.close();

    if(_depth.isValid())
        _depth.destroy();

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
        LOG(ERROR) << "Failed to open device.";
    }

    rc = _device.open(openni::ANY_DEVICE);
    if(rc != openni::Status::STATUS_OK)
    {
        openni::OpenNI::shutdown();
        LOG(ERROR) << "Failed to open device.";
    }

    _device.setImageRegistrationMode(openni::ImageRegistrationMode::IMAGE_REGISTRATION_DEPTH_TO_COLOR);

    rc = _depth.create(_device, openni::SENSOR_DEPTH);
    if(rc == openni::Status::STATUS_OK)
    {
        rc = _depth.start();
        if(rc != openni::STATUS_OK)
        {
            _depth.destroy();
            openni::OpenNI::shutdown();
            LOG(ERROR) << "Failed to start depth stream.";
        }
    }
    else
    {
        openni::OpenNI::shutdown();
        LOG(ERROR) << "Failed to create depth video stream.";
    }

    rc = _color.create(_device, openni::SENSOR_COLOR);
    if(rc == openni::Status::STATUS_OK)
    {
        rc = _color.start();
        if(rc != openni::STATUS_OK)
        {
            _color.destroy();
            openni::OpenNI::shutdown();
            LOG(ERROR) << "Failed to start color stream.";
        }
    }
    else
    {
        openni::OpenNI::shutdown();
        LOG(ERROR) << "Failed to create color video stream.";
    }

    if (!_depth.isValid() && !_color.isValid())
    {
        openni::OpenNI::shutdown();
        LOG(ERROR) << "No valid streams.";
    }

    _depthVideoMode = _depth.getVideoMode();
    _colorVideoMode = _color.getVideoMode();

    _colorVideoMode.setPixelFormat(openni::PixelFormat::PIXEL_FORMAT_RGB888);
    _depthVideoMode.setPixelFormat(openni::PixelFormat::PIXEL_FORMAT_DEPTH_100_UM);
    _colorVideoMode.setFps(30);
    _depthVideoMode.setFps(30);
    _colorVideoMode.setResolution(WIDTH,HEIGHT);
    _depthVideoMode.setResolution(WIDTH,HEIGHT);

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
        LOG(ERROR) << "Depth and color resolution are not the same.";
    }

    LOG(INFO) << "Resolution X: " << _width;
    LOG(INFO) << "Resolution Y: " << _height;
    LOG(INFO) << "FPS: " << _colorVideoMode.getFps();

    _streams.get()[0] = &_depth;
    _streams.get()[1] = &_color;
}

std::vector<float> MHV::OpenNICamera::calculatePointCloud(const uint16_t* depth)
{
    std::vector<float> points;
    points.reserve(_width*_height*3);

#pragma omp parallel for
    for( uint32_t y = 0; y < _height; y++ )
    {
        for( uint32_t x = 0; x < _width; x++ )
        {
            const uint16_t z = depth[y * _width + x];
            if( !z )
            {
                continue;
            }

            float wx, wy, wz;
            openni::Status rc = openni::CoordinateConverter::convertDepthToWorld( _depth, static_cast<float>( x ), static_cast<float>( y ), static_cast<float>( z ), &wx, &wy, &wz );
            if(rc != openni::STATUS_OK)
            {
                LOG(ERROR) << "Can't convert depth to world.";
            }

            points.push_back(wx);
            points.push_back(wy);
            points.push_back(wz);
        }
    }

    return points;
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

        _depth.readFrame(&_depthFrame);
        if(_depthFrame.isValid())
        {
            _utils->setDepthData(_depthFrame.getData());

            auto* depth = static_cast<const uint16_t*>( _depthFrame.getData() );
            std::vector<float> points = calculatePointCloud(depth);
            _utils->setPointCloudData(points.data());
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
