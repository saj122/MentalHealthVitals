#ifndef MEMORY_LINUX_H
#define MEMORY_LINUX_H

#include "Memory.h"

namespace MHV
{
    class MemoryLinux : public Memory
    {
        public:
            MemoryLinux(int width, int height);
            ~MemoryLinux();
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

            int _rgbSharedMemory;
            int _depthSharedMemory;
            int _pointCloudSharedMemory;
            int _width;
            int _height;
    };
}

#endif // MEMORY_LINUX_H
