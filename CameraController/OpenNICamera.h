#ifndef OPENNICAMERA_H
#define OPENNICAMERA_H

#include "Camera.h"

#include <OpenNI.h>

#include <vector>
#include <memory>

namespace MHV
{
    class Memory;
}

namespace MHV
{
    class OpenNICamera : public Camera
    {
        public:
            OpenNICamera(int width, int height);
            ~OpenNICamera() override;
            void init() override;
            void run() override;
            bool isValid() override;
        private:
            std::vector<float> calculatePointCloud(const uint16_t* depth);
        private:
            std::unique_ptr<Memory> _utils;

            openni::Device _device;
            openni::VideoStream _depth;
            openni::VideoStream _color;
            std::unique_ptr<openni::VideoStream*> _streams;
            openni::VideoFrameRef _depthFrame;
            openni::VideoFrameRef _colorFrame;
            openni::VideoMode _depthVideoMode;
            openni::VideoMode _colorVideoMode;

            uint32_t _width;
            uint32_t _height;
    };
}


#endif // OPENNICAMERA_H