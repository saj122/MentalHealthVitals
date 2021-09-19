#ifndef DRUTILS_H
#define DRUTILS_H

#include <QSharedMemory>

class DRUtils
{
    public:
        DRUtils();
        ~DRUtils();
        void setRGBData(const void* data, int size);
        void setDepthData(const void* data, int size);
        const void* getRGBData();
        const void* getDepthData();
    private:
        QSharedMemory _colorSharedMemory;
        QSharedMemory _depthSharedMemory;
};

#endif // DRUTILS_H
