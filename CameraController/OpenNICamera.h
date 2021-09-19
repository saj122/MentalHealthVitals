#ifndef OPENNICAMERA_H
#define OPENNICAMERA_H

#include "Camera.h"

#include <OpenNI.h>

class DRUtils;

class OpenNICamera : Camera
{
    public:
        OpenNICamera();
        ~OpenNICamera();
        void init();
        void run();
    private:
        DRUtils* _utils;

        openni::Device _device;
        openni::VideoStream _depth;
        openni::VideoStream _color;
        openni::VideoStream** _streams;
        openni::VideoFrameRef _depthFrame;
        openni::VideoFrameRef _colorFrame;
        openni::VideoMode _depthVideoMode;
        openni::VideoMode _colorVideoMode;

        int _width;
        int _height;
};

#endif // OPENNICAMERA_H
