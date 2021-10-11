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
            _mem = MHV::MemoryFactory::create(12,12,4*sizeof(float));
        }

        std::unique_ptr<MHV::Memory> _mem;
};

TEST_F(MemoryTest, TestRGBData)
{
    _mem->setRGBData("Hello World");
    EXPECT_STREQ("Hello World", (char*) _mem->getRGBData());
}

TEST_F(MemoryTest, TestDepthData)
{
    std::string str("Hello World");
    _mem->setDepthData(str.data());
    EXPECT_STREQ(str.data(),(char*)_mem->getDepthData());
}

TEST_F(MemoryTest, TestPointCloudData)
{
    float* points = new float[4];
    points[0] = 0.0f;
    points[1] = 1.0f;
    points[2] = 2.0f;
    points[3] = 3.0f;

    _mem->setPointCloudData(points);

    const float* data = _mem->getPointCloudData();
    EXPECT_EQ(data[0], points[0]);
    EXPECT_EQ(data[1], points[1]);
    EXPECT_EQ(data[2], points[2]);
    EXPECT_EQ(data[3], points[3]);
}
