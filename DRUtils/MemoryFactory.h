//
// Created by stephen on 9/27/21.
//

#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H

#ifdef _WIN32
    #include "MemoryWindows.h"
#else
    #include "MemoryLinux.h"
#endif

#include <memory>

namespace MHV
{
    class MemoryFactory
    {
        public:
            static std::unique_ptr<MHV::Memory> create(size_t rgb_size)
            {
            #ifdef _WIN32
                return std::make_unique<MHV::MemoryWindows>(rgb_size);
            #else
                return std::make_unique<MHV::MemoryLinux>(rgb_size);
            #endif
            }

            static std::unique_ptr<MHV::Memory> create(size_t rgb_size, size_t depth_size, size_t point_cloud_size)
            {
            #ifdef _WIN32
                return std::make_unique<MHV::MemoryWindows>(rgb_size, depth_size, point_cloud_size);
            #else
                return std::make_unique<MHV::MemoryLinux>(rgb_size, depth_size, point_cloud_size);
            #endif
            }
    };
}

#endif // MEMORYFACTORY_H
