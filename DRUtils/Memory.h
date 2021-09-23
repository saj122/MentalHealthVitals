#ifndef MEMORY_H
#define MEMORY_H

#include <memory>

class QSharedMemory;

namespace MHV
{
    class Memory
    {
        public:
            Memory(int width, int height);
            ~Memory();
            void setRGBData(const void* data, int size);
            void setDepthData(const void* data, int size);
            void setPointCloudData(const float* data, int size);
            const unsigned char* getRGBData();
            const unsigned char* getDepthData();
            const float* getPointCloudData();
        private:
            std::unique_ptr<QSharedMemory> _colorSharedMemory;
            std::unique_ptr<QSharedMemory> _depthSharedMemory;
            std::unique_ptr<QSharedMemory> _pointCloudSharedMemory;

            std::unique_ptr<unsigned char[]> _depthData;
            std::unique_ptr<unsigned char[]> _rgbData;
            std::unique_ptr<float[]> _pointCloudData;
    };
}

#endif // DRUTILS_H