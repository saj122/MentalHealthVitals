#include "MemoryUnix.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <cstring>

#include <glog/logging.h>

MHV::MemoryUnix::MemoryUnix(size_t rgb_size) : _rgbData(new unsigned char[rgb_size]),
                                               _detectionData(new int[4]),
                                               _emotionData(new char[100]),
                                               _rgbSharedMemory(0),
                                               _detectionMemory(0),
                                               _emotionMemory(0),
                                               _rgb_size(rgb_size),
                                               _rgbSemID(0),
                                               _detectSemID(0),
                                               _emotionSemID(0)
{

}

MHV::MemoryUnix::~MemoryUnix()
{
    delete[] _rgbData;
    delete[] _detectionData;
    delete[] _emotionData;

    shmctl(_rgbSharedMemory,IPC_RMID,NULL);
    shmctl(_detectionMemory,IPC_RMID,NULL);
    shmctl(_emotionMemory,IPC_RMID,NULL);
    
    semctl(_rgbSemID, 0, IPC_RMID);
    semctl(_detectSemID, 0, IPC_RMID);
    semctl(_emotionSemID, 0, IPC_RMID);
}

void MHV::MemoryUnix::setSemaphore(struct sembuf& buf, int id, int key)
{
    struct sembuf sem_buf;
    int retVal;
    
    id = semget((key_t)key, 1, IPC_CREAT | IPC_EXCL | 0666);
    
    if(id >= 0)
    {
        sem_buf.sem_op = 1;
        sem_buf.sem_flg = 0;
        sem_buf.sem_num = 0;
        
        retVal = semop(id, &sem_buf, 1);
        if(retVal == -1)
        {
            LOG(ERROR) << "RGB set semaphore operation failed.";
            return;
        }
    }
    else if (errno == EEXIST)
    {
        int ready = 0;
        
        id = semget((key_t)1234, 1, 0);
        if(id < 0)
        {
            LOG(ERROR) << "RGB set semaphore get failed.";
            return;
        }
        
        sem_buf.sem_num = 0;
        sem_buf.sem_op = 0;
        sem_buf.sem_flg = SEM_UNDO;
        retVal = semop(id, &sem_buf, 1);
        if(retVal == -1)
        {
            LOG(ERROR) << "RGB set semaphore locked.";
            return;
        }
    }
    
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    retVal = semop(id, &sem_buf, 1);
    if(retVal == -1)
    {
        LOG(ERROR) << "RGB set semaphore locked.";
        return;
    }
}

void MHV::MemoryUnix::releaseResource(struct sembuf& buf, int id)
{
    buf.sem_op = 1;
    semop(id, &buf, 1);

    id = semget((key_t)1234, 1, 0);
    semctl(id, 0, IPC_RMID);
}

void MHV::MemoryUnix::setRGBData(const void* data)
{
    struct sembuf buf;
    
    _rgbSharedMemory = shmget((key_t)123, _rgb_size, 0666|IPC_CREAT);
    if(_rgbSharedMemory == -1)
    {
        LOG(ERROR) << "Couldn't get RGB shared memory.";
        return;
    }

    void* shmData = shmat(_rgbSharedMemory, NULL, 0);
    
    setSemaphore(buf, _rgbSemID, 1234);
    
    std::memcpy(shmData, data, _rgb_size);
    
    releaseResource(buf, _rgbSemID);

    shmdt(shmData);
}

void MHV::MemoryUnix::setDetectionBox(const int* data)
{
    struct sembuf buf;
    
    _detectionMemory = shmget((key_t)987, 4*sizeof(int), 0666|IPC_CREAT);
    if(_detectionMemory == -1)
    {
        LOG(ERROR) << "Couldn't get detection shared memory.";
        return;
    }
    float* shmData = (float*)shmat(_detectionMemory, NULL, 0);
    
    setSemaphore(buf, _detectSemID, 4567);

    std::memcpy(shmData, data, 4*sizeof(int));

    releaseResource(buf, _detectSemID);
    
    shmdt(shmData);
}

void MHV::MemoryUnix::setEmotionState(const char* data)
{
    struct sembuf buf;
    
    _emotionMemory = shmget((key_t)654, 100*sizeof(char), 0666|IPC_CREAT);
    if(_emotionMemory == -1)
    {
        LOG(ERROR) << "Couldn't get emotion shared memory.";
        return;
    }
    float* shmData = (float*)shmat(_emotionMemory, NULL, 0);

    setSemaphore(buf, _emotionSemID, 5678);
    
    std::memcpy(shmData, data, 100*sizeof(char));
    
    releaseResource(buf, _emotionSemID);

    shmdt(shmData);
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
