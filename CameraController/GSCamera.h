#ifndef GSCAMERA_H
#define GSCAMERA_H

#include "Camera.h"

#include <memory>

#include <gst/gst.h>

namespace MHV
{
    class Memory;
}

namespace MHV
{
    class GSCamera : public Camera
    {
        public:
            GSCamera(int width, int height);
            ~GSCamera() override;
            void init() override;
            void run() override;
            bool isValid() override;
        private:
            std::unique_ptr<Memory> _utils;

            GstElement* _pipeline;
            GstBuffer* _buffer;
            GstSample* _sample;
            GstElement* _sink;

            uint32_t _width;
            uint32_t _height;
    };
}


#endif // GSCAMERA_H
