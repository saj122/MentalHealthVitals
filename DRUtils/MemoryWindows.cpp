//
// Created by stephen on 9/26/21.
//

#include <windows.h>
#include <conio.h>

#include "glog/logging.h"

#include "MemoryWindows.h"

MHV::MemoryWindows::MemoryWindows(size_t rgb_size, size_t depth_size, size_t point_cloud_size) :  _rgbData(new unsigned char[rgb_size]),
                                                                                                  _depthData(new unsigned char[depth_size]),
                                                                                                  _pointCloudData(new float[point_cloud_size]),
                                                                                                  _rgbSharedMemory("123"),
                                                                                                  _depthSharedMemory("456"),
                                                                                                  _pointCloudSharedMemory("789"),
                                                                                                  _rgb_size(rgb_size),
                                                                                                  _depth_size(depth_size),
                                                                                                  _point_cloud_size(point_cloud_size)
{
}

MHV::MemoryWindows::~MemoryWindows()
{
    delete[] _rgbData;
    delete[] _depthData;
    delete[] _pointCloudData;
}

void MHV::MemoryWindows::setRGBData(const void* data)
{
    HANDLE hMapFile;
    unsigned char* pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    
        NULL,                    
        PAGE_READWRITE,         
        0,                       
        (DWORD)BUF_SIZE,                
        _rgbSharedMemory.data());                 

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not create file mapping object: " << GetLastError();
        return;
    }
    pBuf = (unsigned char*)MapViewOfFile(hMapFile,   
        FILE_MAP_ALL_ACCESS, 
        0,
        0,
        _rgb_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return;
    }


    CopyMemory(pBuf, data, _width*_height*3);

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
}

void MHV::MemoryWindows::setDepthData(const void* data)
{
    HANDLE hMapFile;
    unsigned char* pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        (DWORD)BUF_SIZE,
        _depthSharedMemory.data());

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not create file mapping object: " << GetLastError();
        return;
    }
    pBuf = (unsigned char*)MapViewOfFile(hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        _depth_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return;
    }


    CopyMemory(pBuf, data, BUF_SIZE);

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
}

void MHV::MemoryWindows::setPointCloudData(const float* data)
{
    HANDLE hMapFile;
    float* pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        (DWORD)BUF_SIZE,
        _pointCloudSharedMemory.data());

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not create file mapping object: " << GetLastError();
        return;
    }
    pBuf = (float*)MapViewOfFile(hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        _point_cloud_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return;
    }


    CopyMemory(pBuf, data, BUF_SIZE);

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);
}

const unsigned char* MHV::MemoryWindows::getRGBData()
{
    HANDLE hMapFile;
    unsigned char* pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   
        FALSE,                 
        _rgbSharedMemory.data());               

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not open file mapping object: " << GetLastError();
        return nullptr;
    }

    pBuf = (unsigned char*)MapViewOfFile(hMapFile, 
        FILE_MAP_ALL_ACCESS,  
        0,
        0,
        _rgb_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return nullptr;
    }

    CopyMemory(_rgbData, pBuf, BUF_SIZE);

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

    return _rgbData;
}

const unsigned char* MHV::MemoryWindows::getDepthData()
{
    HANDLE hMapFile;
    unsigned char* pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        _depthSharedMemory.data());

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not open file mapping object: " << GetLastError();
        return nullptr;
    }

    pBuf = (unsigned char*)MapViewOfFile(hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        _depth_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return nullptr;
    }

    CopyMemory(_depthData, pBuf, BUF_SIZE);
    
    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

    return _depthData;
}

const float* MHV::MemoryWindows::getPointCloudData()
{
    HANDLE hMapFile;
    float* pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        _rgbSharedMemory.data());

    if (hMapFile == NULL)
    {
        LOG(ERROR) << "Could not open file mapping object: " << GetLastError();
        return nullptr;
    }

    pBuf = (float*)MapViewOfFile(hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        _point_cloud_size);

    if (pBuf == NULL)
    {
        LOG(ERROR) << "Could not map view of file: " << GetLastError();

        CloseHandle(hMapFile);

        return nullptr;
    }

    CopyMemory(_pointCloudData, pBuf, BUF_SIZE);

    UnmapViewOfFile(pBuf);

    CloseHandle(hMapFile);

    return _pointCloudData;
}