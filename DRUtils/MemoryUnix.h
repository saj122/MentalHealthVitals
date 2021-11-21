#ifndef MEMORY_LINUX_H
#define MEMORY_LINUX_H

#include <cstddef>
#include "Memory.h"

#include <sys/sem.h>

#define NUMSEMS 2

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
        
            int _rc;
            int _rgbSemID;
            int _depthSemID;
            int _pointCloudSemID;
            int _detectSemID;
            int _emotionSemID;
            struct sembuf _operations[2];
            short _sarray[NUMSEMS];
    };
}

#endif // MEMORY_LINUX_H
