#ifndef MEMORY_LINUX_H
#define MEMORY_LINUX_H

#include <cstddef>
#include "Memory.h"

namespace MHV
{
    class MemoryUnix : public Memory
    {
        public:
            MemoryUnix(size_t rgb_size);
            MemoryUnix(size_t rgb_size, size_t depth_size, size_t point_cloud_size);
            ~MemoryUnix() override;
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
            size_t _rgb_size;
            size_t _depth_size;
            size_t _point_cloud_size;
    };
}

#endif // MEMORY_LINUX_H
