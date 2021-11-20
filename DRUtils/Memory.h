//
// Created by stephen on 9/26/21.
//

#ifndef MEMORY_H
#define MEMORY_H

namespace MHV
{
    class Memory
    {
        public:
            virtual ~Memory() = default;
            virtual void setRGBData(const void* data) = 0;
            virtual void setDepthData(const void* data) = 0;
            virtual void setPointCloudData(const float* data) = 0;
            virtual void setDetectionBox(const int* data) = 0;
            virtual void setEmotionState(const char* data) = 0;
            virtual const unsigned char* getRGBData() = 0;
            virtual const unsigned char* getDepthData() = 0;
            virtual const float* getPointCloudData() = 0;
            virtual const int* getDetectionBox() = 0;
            virtual const char* getEmotionState() = 0;
    };
}

#endif // MEMORY_H
