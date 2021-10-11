#include "MemoryLinux.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include <glog/logging.h>

MHV::MemoryLinux::MemoryLinux(size_t rgb_size, size_t depth_size, size_t point_cloud_size) : _rgbData(new unsigned char[rgb_size]),
                                                                                    _depthData(new unsigned char[depth_size]),
                                                                                    _pointCloudData(new float[point_cloud_size]),
                                                                                    _rgbSharedMemory(0),
                                                                                    _depthSharedMemory(0),
                                                                                    _pointCloudSharedMemory(0),
                                                                                    _rgb_size(rgb_size),
                                                                                    _depth_size(depth_size),
                                                                                    _point_cloud_size(point_cloud_size)
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
    _rgbSharedMemory = shmget((key_t)123, _rgb_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _rgbSharedMemory == -1) << "Couldn't set RGB shared memory.";

    void* shmData = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _rgb_size);

    shmdt(shmData);
}

void MHV::MemoryLinux::setDepthData(const void* data)
{
    _depthSharedMemory = shmget((key_t)456, _depth_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _depthSharedMemory == -1) << "Couldn't set depth shared memory.";

    void* shmData = shmat(_depthSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _depth_size);

    shmdt(shmData);
}

void MHV::MemoryLinux::setPointCloudData(const float* data)
{
    _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _pointCloudSharedMemory == -1) << "Couldn't set point cloud shared memory.";

    float* shmData = (float*)shmat(_pointCloudSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _point_cloud_size);

    shmdt(shmData);
}

const unsigned char* MHV::MemoryLinux::getRGBData()
{
    _rgbSharedMemory = shmget((key_t)123, _rgb_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _rgbSharedMemory == -1) << "Couldn't get RGB shared memory.";

    void* image = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(_rgbData, image, _rgb_size);

    shmdt(image);

    return _rgbData;
}

const unsigned char* MHV::MemoryLinux::getDepthData()
{
    _depthSharedMemory = shmget((key_t)456,  _depth_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _depthSharedMemory == -1) << "Couldn't get depth shared memory.";

    void* image = shmat(_depthSharedMemory, NULL, 0);

    std::memcpy(_depthData, image, _depth_size);

    shmdt(image);

    return _depthData;
}

const float* MHV::MemoryLinux::getPointCloudData()
{
    _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size, 0666|IPC_CREAT);
    LOG_IF(ERROR, _pointCloudSharedMemory == -1) << "Couldn't get point cloud shared memory.";

    void* cloud = shmat(_pointCloudSharedMemory, NULL, 0);

    std::memcpy(_pointCloudData, cloud, _point_cloud_size);

    shmdt(cloud);

    return _pointCloudData;
}
