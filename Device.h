#ifndef DEVICE_H
#define DEVICE_H

#include <OpenNI.h>

class Device
{
    public:
        virtual void init() = 0;
        virtual openni::Device& getDevice() = 0;
        virtual openni::VideoStream& getColorStream() = 0;
        virtual openni::VideoStream& getDepthStream() = 0;
};

#endif // DEVICE_H
