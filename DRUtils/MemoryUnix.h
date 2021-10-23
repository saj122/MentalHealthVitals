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
            void setDetectionBoxes(const float* data) override;
            void setEmotionState(const char* data) override;

            const unsigned char* getRGBData() override;
            const unsigned char* getDepthData() override;
            const float* getPointCloudData() override;
            const float* getDetectionBoxes() override;
            const char* getEmotionState() override;
        private:
            unsigned char* _depthData;
            unsigned char* _rgbData;
            float* _pointCloudData;
            float* _detectionData;
            char* _emotionData;

            int _rgbSharedMemory;
            int _depthSharedMemory;
            int _pointCloudSharedMemory;
            int _detectionMemory;
            int _emotionMemory;
            size_t _rgb_size;
            size_t _depth_size;
            size_t _point_cloud_size;
    };
}

#endif // MEMORY_LINUX_H
