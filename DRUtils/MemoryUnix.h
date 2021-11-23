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
            ~MemoryUnix();
            void setRGBData(const void* data);
            void setDetectionBox(const int* data);
            void setEmotionState(const char* data);

            const unsigned char* getRGBData();
            const int* getDetectionBox();
            const char* getEmotionState();
        private:
            void setSemaphore(struct sembuf& buf, int id, int key);
            void releaseResource(struct sembuf& buf, int id);
        private:
            unsigned char* _rgbData;
            int* _detectionData;
            char* _emotionData;

            int _rgbSharedMemory;
            int _detectionMemory;
            int _emotionMemory;
            size_t _rgb_size;
        
            int _rgbSemID;
            int _detectSemID;
            int _emotionSemID;
    };
}

#endif // MEMORY_LINUX_H
