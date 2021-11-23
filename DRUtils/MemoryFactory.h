//
// Created by stephen on 9/27/21.
//

#ifndef MEMORYFACTORY_H
#define MEMORYFACTORY_H

#include "MemoryUnix.h"

#include <memory>

namespace MHV
{
    class MemoryFactory
    {
        public:
            static std::unique_ptr<MHV::Memory> create(size_t rgb_size)
            {
                return std::make_unique<MHV::MemoryUnix>(rgb_size);
            }
    };
}

#endif // MEMORYFACTORY_H
