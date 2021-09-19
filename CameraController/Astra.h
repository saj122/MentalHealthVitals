#ifndef ASTRA_H
#define ASTRA_H

#include "Device.h"

#include <OpenNI.h>

class DRUtils;

#define MAX_DEPTH 10000

class Astra : public Device
{
    public:
        Astra();
        ~Astra();
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

#endif // ASTRA_H
