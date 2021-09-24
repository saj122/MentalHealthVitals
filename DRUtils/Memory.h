#ifndef MEMORY_H
#define MEMORY_H

namespace MHV
{
    class Memory
    {
        public:
            Memory(int width, int height);
            ~Memory();
            void setRGBData(const void* data);
            void setDepthData(const void* data);
            void setPointCloudData(const float* data);
            const unsigned char* getRGBData();
            const unsigned char* getDepthData();
            const float* getPointCloudData();
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

#endif // DRUTILS_H
