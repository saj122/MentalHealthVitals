//
// Created by stephen on 9/30/21.
//
#include "MemoryFactory.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

class MemoryTest : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            _mem = MHV::MemoryFactory::create(12);
        }

        std::unique_ptr<MHV::Memory> _mem;
};

TEST_F(MemoryTest, TestRGBData)
{
    _mem->setRGBData("Hello World");
    EXPECT_STREQ("Hello World", (char*) _mem->getRGBData());
}