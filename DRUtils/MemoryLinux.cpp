#include "MemoryLinux.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include <glog/logging.h>

MHV::MemoryLinux::MemoryLinux(int width, int height) : _width(width),
                                                       _height(height),
                                                       _rgbData(new unsigned char[width*height*3]),
                                                       _depthData(new unsigned char[width*height*2]),
                                                       _pointCloudData(new float[width*height*3])
{
}

MHV::MemoryLinux::~MemoryLinux()
{
    delete[] _rgbData;
    delete[] _depthData;
    delete[] _pointCloudData;

    shmctl(_rgbSharedMemory,IPC_RMID,NULL);
    shmctl(_depthSharedMemory,IPC_RMID,NULL);
    shmctl(_pointCloudSharedMemory,IPC_RMID,NULL);
}

void MHV::MemoryLinux::setRGBData(const void* data)
{
    _rgbSharedMemory = shmget((key_t)123, _width*_height*3*sizeof(unsigned char), 0666|IPC_CREAT);
    LOG_IF(ERROR, _rgbSharedMemory == -1) << "Couldn't set RGB shared memory.";

    void* shmData = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _width*_height*3);

    shmdt(shmData);
}

void MHV::MemoryLinux::setDepthData(const void* data)
{
    _depthSharedMemory = shmget((key_t)456, _width*_height*2*sizeof(unsigned char), 0666|IPC_CREAT);
    LOG_IF(ERROR, _depthSharedMemory == -1) << "Couldn't set depth shared memory.";

    void* shmData = shmat(_depthSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _width*_height*2);

    shmdt(shmData);
}

void MHV::MemoryLinux::setPointCloudData(const float* data)
{
    _pointCloudSharedMemory = shmget((key_t)789, _width*_height*3*sizeof(float), 0666|IPC_CREAT);
    LOG_IF(ERROR, _pointCloudSharedMemory == -1) << "Couldn't set point cloud shared memory.";

    float* shmData = (float*)shmat(_pointCloudSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _width*_height*3*sizeof(float));

    shmdt(shmData);
}

const unsigned char* MHV::MemoryLinux::getRGBData()
{
    _rgbSharedMemory = shmget((key_t)123, _width*_height*3, 0666|IPC_CREAT);
    LOG_IF(ERROR, _rgbSharedMemory == -1) << "Couldn't get RGB shared memory.";

    void* image = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(_rgbData, image, _width*_height*3);

    shmdt(image);

    return _rgbData;
}

const unsigned char* MHV::MemoryLinux::getDepthData()
{
    _depthSharedMemory = shmget((key_t)456,  _width*_height*2, 0666|IPC_CREAT);
    LOG_IF(ERROR, _depthSharedMemory == -1) << "Couldn't get depth shared memory.";

    void* image = shmat(_depthSharedMemory, NULL, 0);

    std::memcpy(_depthData, image, _width*_height*2);

    shmdt(image);

    return _depthData;
}

const float* MHV::MemoryLinux::getPointCloudData()
{
    _pointCloudSharedMemory = shmget((key_t)789, _width*_height*12, 0666|IPC_CREAT);
    LOG_IF(ERROR, _pointCloudSharedMemory == -1) << "Couldn't get point cloud shared memory.";

    void* image = shmat(_pointCloudSharedMemory, NULL, 0);

    std::memcpy(_pointCloudData, image, _width*_height*12);

    shmdt(image);

    return _pointCloudData;
}
