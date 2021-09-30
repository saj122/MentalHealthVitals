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
            static std::unique_ptr<MHV::Memory> create()
            {
            #ifdef _WIN32
                return std::make_unique<MHV::MemoryWindows>(640,480);
            #else
                return std::make_unique<MHV::MemoryLinux>(640,480);
            #endif
            }
    };
}

#endif // MEMORYFACTORY_H
