//
// Created by stephen on 9/26/21.
//

#ifndef MEMORYWINDOWS_H
#define MEMORYWINDOWS_H

#include "Memory.h"

#include <string>

namespace MHV
{
    class MemoryWindows : public Memory
    {
        public:
            MemoryWindows(size_t width, size_t height);
            ~MemoryWindows();
            void setRGBData(const void* data) override;
            void setDepthData(const void* data) override;
            void setPointCloudData(const float* data) override;
            const unsigned char* getRGBData() override;
            const unsigned char* getDepthData() override;
            const float* getPointCloudData() override;
        private:
            unsigned char* _depthData;
            unsigned char* _rgbData;
            float* _pointCloudData;

            std::string _rgbSharedMemory;
            std::string _depthSharedMemory;
            std::string _pointCloudSharedMemory;
            size_t _width;
            size_t _height;
    };
}

#endif // MEMORYWINDOWS_H
