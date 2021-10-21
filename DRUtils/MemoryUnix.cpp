#include "MemoryUnix.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include <glog/logging.h>

MHV::MemoryUnix::MemoryUnix(size_t rgb_size) : _rgbData(new unsigned char[rgb_size]),
                                                 _depthData(nullptr),
                                                 _pointCloudData(nullptr),
                                                 _rgbSharedMemory(0),
                                                 _depthSharedMemory(0),
                                                 _pointCloudSharedMemory(0),
                                                 _rgb_size(rgb_size),
                                                 _depth_size(0),
                                                 _point_cloud_size(0)
{

}

MHV::MemoryUnix::MemoryUnix(size_t rgb_size, size_t depth_size, size_t point_cloud_size) : _rgbData(new unsigned char[rgb_size]),
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

MHV::MemoryUnix::~MemoryUnix()
{
    delete[] _rgbData;
    if(_depthData)
        delete[] _depthData;
    if(_pointCloudData)
        delete[] _pointCloudData;

    shmctl(_rgbSharedMemory,IPC_RMID,NULL);
    shmctl(_depthSharedMemory,IPC_RMID,NULL);
    shmctl(_pointCloudSharedMemory,IPC_RMID,NULL);
}

void MHV::MemoryUnix::setRGBData(const void* data)
{
    _rgbSharedMemory = shmget((key_t)123, _rgb_size, 0666|IPC_CREAT);
    if(_rgbSharedMemory == -1)
    {
        LOG(ERROR) << "Couldn't get RGB shared memory.";
        return;
    }

    void* shmData = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(shmData, data, _rgb_size);

    shmdt(shmData);
}

void MHV::MemoryUnix::setDepthData(const void* data)
{
    if(_depthData)
    {
        _depthSharedMemory = shmget((key_t)456, _depth_size, 0666|IPC_CREAT);
        if(_depthSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get depth shared memory.";
            return;
        }

        void* shmData = shmat(_depthSharedMemory, NULL, 0);

        std::memcpy(shmData, data, _depth_size);

        shmdt(shmData);
    }
}

void MHV::MemoryUnix::setPointCloudData(const float* data)
{
    if(_pointCloudData)
    {
        _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size, 0666|IPC_CREAT);
        if(_pointCloudSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get point cloud shared memory.";
            return;
        }
        float* shmData = (float*)shmat(_pointCloudSharedMemory, NULL, 0);

        std::memcpy(shmData, data, _point_cloud_size);

        shmdt(shmData);
    }
}

const unsigned char* MHV::MemoryUnix::getRGBData()
{
    _rgbSharedMemory = shmget((key_t)123, _rgb_size, 0666|IPC_CREAT);
    if(_rgbSharedMemory == -1)
    {
        LOG(ERROR) << "Couldn't get RGB shared memory.";
        return nullptr;
    }

    void* image = shmat(_rgbSharedMemory, NULL, 0);

    std::memcpy(_rgbData, image, _rgb_size);

    shmdt(image);

    return _rgbData;
}

const unsigned char* MHV::MemoryUnix::getDepthData()
{
    if(_depthData)
    {
        _depthSharedMemory = shmget((key_t)456,  _depth_size, 0666|IPC_CREAT);
        if(_depthSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get depth shared memory.";
            return nullptr;
        }

        void* image = shmat(_depthSharedMemory, NULL, 0);

        std::memcpy(_depthData, image, _depth_size);

        shmdt(image);
    }
    return _depthData;
}

const float* MHV::MemoryUnix::getPointCloudData()
{
    if(_pointCloudData)
    {
        _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size, 0666|IPC_CREAT);
        if(_pointCloudSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get point cloud shared memory.";
            return nullptr;
        }

        void* cloud = shmat(_pointCloudSharedMemory, NULL, 0);

        std::memcpy(_pointCloudData, cloud, _point_cloud_size);

        shmdt(cloud);
    }

    return _pointCloudData;
}
