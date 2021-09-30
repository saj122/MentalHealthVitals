//
// Created by stephen on 9/26/21.
//

#include <windows.h>
#include <conio.h>

#include "glog/logging.h"

#include "MemoryWindows.h"

MHV::MemoryWindows::MemoryWindows(size_t width, size_t height) :  _rgbData(new unsigned char[width * height * 3]),
                                                            _depthData(new unsigned char[width * height * 2]),
                                                            _pointCloudData(new float[width * height * 3]),
                                                            _rgbSharedMemory("123"),
                                                            _depthSharedMemory("456"),
                                                            _pointCloudSharedMemory("789"),
                                                            _width(width),
                                                            _height(height)                       
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
    const size_t BUF_SIZE = _width * _height * 3;

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
        BUF_SIZE);

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
    const size_t BUF_SIZE = _width * _height * 2;

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
        BUF_SIZE);

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
    const size_t BUF_SIZE = _width * _height * 3 * 4;

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
        BUF_SIZE);

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
    const size_t BUF_SIZE = _width * _height * 3;

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
        BUF_SIZE);

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
    const size_t BUF_SIZE = _width * _height * 2;

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
        BUF_SIZE);

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
    const size_t BUF_SIZE = _width * _height * 3 * 4;

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
        BUF_SIZE);

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