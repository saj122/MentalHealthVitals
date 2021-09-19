#ifndef DRUTILS_H
#define DRUTILS_H

class QSharedMemory;

class DRUtils
{
    public:
        DRUtils();
        ~DRUtils();
        void setRGBData(const void* data, int size);
        void setDepthData(const void* data, int size);
        const unsigned char* getRGBData();
        const unsigned char* getDepthData();
    private:
        QSharedMemory* _colorSharedMemory;
        QSharedMemory* _depthSharedMemory;

        unsigned char* _depthData;
        unsigned char* _rgbData;
};

#endif // DRUTILS_H
