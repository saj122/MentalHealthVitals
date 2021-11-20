#include "MemoryUnix.h"

#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstring>

#include <glog/logging.h>

MHV::MemoryUnix::MemoryUnix(size_t rgb_size) : _rgbData(new unsigned char[rgb_size]),
                                               _depthData(nullptr),
                                               _pointCloudData(nullptr),
                                               _detectionData(new int[4]),
                                               _emotionData(new char[100]),
                                               _rgbSharedMemory(0),
                                               _depthSharedMemory(0),
                                               _pointCloudSharedMemory(0),
                                               _detectionMemory(0),
                                               _emotionMemory(0),
                                               _rgb_size(rgb_size),
                                               _depth_size(0),
                                               _point_cloud_size(0)
{

}

MHV::MemoryUnix::MemoryUnix(size_t rgb_size, size_t depth_size, size_t point_cloud_size) : _rgbData(new unsigned char[rgb_size]),
                                                                                           _depthData(new unsigned char[depth_size]),
                                                                                           _pointCloudData(new float[point_cloud_size]),
                                                                                           _detectionData(new int[4]),
                                                                                           _emotionData(new char[100]),
                                                                                           _rgbSharedMemory(0),
                                                                                           _depthSharedMemory(0),
                                                                                           _pointCloudSharedMemory(0),
                                                                                           _detectionMemory(0),
                                                                                           _emotionMemory(0),
                                                                                           _rgb_size(rgb_size),
                                                                                           _depth_size(depth_size),
                                                                                           _point_cloud_size(point_cloud_size)
{

}

MHV::MemoryUnix::~MemoryUnix()
{
    delete[] _rgbData;
    delete[] _detectionData;
    delete[] _emotionData;
    if(_depthData)
        delete[] _depthData;
    if(_pointCloudData)
        delete[] _pointCloudData;

    shmctl(_rgbSharedMemory,IPC_RMID,NULL);
    shmctl(_depthSharedMemory,IPC_RMID,NULL);
    shmctl(_pointCloudSharedMemory,IPC_RMID,NULL);
    shmctl(_detectionMemory,IPC_RMID,NULL);
    shmctl(_emotionMemory,IPC_RMID,NULL);
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
        _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size*4, 0666|IPC_CREAT);
        if(_pointCloudSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get point cloud shared memory.";
            return;
        }
        float* shmData = (float*)shmat(_pointCloudSharedMemory, NULL, 0);

        std::memcpy(shmData, data, _point_cloud_size*4);

        shmdt(shmData);
    }
}

void MHV::MemoryUnix::setDetectionBox(const int* data)
{
    if(_detectionData)
    {
        _detectionMemory = shmget((key_t)987, 4*sizeof(int), 0666|IPC_CREAT);
        if(_detectionMemory == -1)
        {
            LOG(ERROR) << "Couldn't get detection shared memory.";
            return;
        }
        float* shmData = (float*)shmat(_detectionMemory, NULL, 0);

        std::memcpy(shmData, data, 4*sizeof(int));

        shmdt(shmData);
    }
}

void MHV::MemoryUnix::setEmotionState(const char* data)
{
    if(_emotionData)
    {
        _emotionMemory = shmget((key_t)654, 100*sizeof(char), 0666|IPC_CREAT);
        if(_emotionMemory == -1)
        {
            LOG(ERROR) << "Couldn't get emotion shared memory.";
            return;
        }
        float* shmData = (float*)shmat(_emotionMemory, NULL, 0);

        std::memcpy(shmData, data, 100*sizeof(char));

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
        _pointCloudSharedMemory = shmget((key_t)789, _point_cloud_size*4, 0666|IPC_CREAT);
        if(_pointCloudSharedMemory == -1)
        {
            LOG(ERROR) << "Couldn't get point cloud shared memory.";
            return nullptr;
        }

        void* cloud = shmat(_pointCloudSharedMemory, NULL, 0);

        std::memcpy(_pointCloudData, cloud, _point_cloud_size*4);

        shmdt(cloud);
    }

    return _pointCloudData;
}

const int* MHV::MemoryUnix::getDetectionBox()
{
    if(_detectionData)
    {
        _detectionMemory = shmget((key_t)987, 4*sizeof(int), 0666|IPC_CREAT);
        if(_detectionMemory == -1)
        {
            LOG(ERROR) << "Couldn't get detection shared memory.";
            return nullptr;
        }

        void* box = shmat(_detectionMemory, NULL, 0);

        std::memcpy(_detectionData, box, 4*sizeof(int));

        shmdt(box);
    }

    return _detectionData;
}

const char* MHV::MemoryUnix::getEmotionState()
{
    if(_emotionData)
    {
        _emotionMemory = shmget((key_t)654,  100*sizeof(char), 0666|IPC_CREAT);
        if(_emotionMemory == -1)
        {
            LOG(ERROR) << "Couldn't get emotion shared memory.";
            return nullptr;
        }

        void* emot = shmat(_emotionMemory, NULL, 0);

        std::memcpy(_emotionData, emot, 100*sizeof(char));

        shmdt(emot);
    }
    return _emotionData;
}