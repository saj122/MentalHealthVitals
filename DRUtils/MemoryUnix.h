#ifndef MEMORY_LINUX_H
#define MEMORY_LINUX_H

#include "Memory.h"

#include <sys/sem.h>

#include <cstddef>

namespace MHV
{
    class MemoryUnix : public Memory
    {
        public:
            MemoryUnix(size_t rgb_size);
            MemoryUnix(size_t rgb_size, size_t depth_size, size_t point_cloud_size);
            ~MemoryUnix();
            void setRGBData(const void* data);
            void setDepthData(const void* data);
            void setPointCloudData(const float* data);
            void setDetectionBox(const int* data);
            void setEmotionState(const char* data);

            const unsigned char* getRGBData();
            const unsigned char* getDepthData();
            const float* getPointCloudData();
            const int* getDetectionBox();
            const char* getEmotionState();
        private:
            void setSemaphore(struct sembuf& buf, int id, int key);
            void releaseResource(struct sembuf& buf, int id);
        private:
            unsigned char* _depthData;
            unsigned char* _rgbData;
            float* _pointCloudData;
            int* _detectionData;
            char* _emotionData;

            int _rgbSharedMemory;
            int _depthSharedMemory;
            int _pointCloudSharedMemory;
            int _detectionMemory;
            int _emotionMemory;
            size_t _rgb_size;
            size_t _depth_size;
            size_t _point_cloud_size;
        
            int _rgbSemID;
            int _depthSemID;
            int _pointCloudSemID;
            int _detectSemID;
            int _emotionSemID;
    };
}

#endif // MEMORY_LINUX_H
