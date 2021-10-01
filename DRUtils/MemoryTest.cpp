//
// Created by stephen on 9/30/21.
//
#include "MemoryFactory.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

TEST(MemoryTest, TestRGBData)
{
    std::unique_ptr<MHV::Memory> mem = MHV::MemoryFactory::create();
    std::string str("Hello World");
    mem->setRGBData(str.data());
    std::string rStr;
    rStr.append((char*)mem->getRGBData());
    EXPECT_STREQ(str.data(),rStr.data());
}

TEST(MemoryTest, TestDepthData)
{
    std::unique_ptr<MHV::Memory> mem = MHV::MemoryFactory::create();
    std::string str("Hello World");
    mem->setDepthData(str.data());
    std::string rStr;
    rStr.append((char*)mem->getDepthData());
    EXPECT_STREQ(str.data(),rStr.data());
}

TEST(MemoryTest, TestPointCloudData)
{
    std::unique_ptr<MHV::Memory> mem = MHV::MemoryFactory::create();
    float* points = new float[4];
    points[0] = 0.0f;
    points[1] = 1.0f;
    points[2] = 2.0f;
    points[3] = 3.0f;

    mem->setPointCloudData(points);

    const float* data = mem->getPointCloudData();
    EXPECT_EQ(data[0], points[0]);
    EXPECT_EQ(data[1], points[1]);
    EXPECT_EQ(data[2], points[2]);
    EXPECT_EQ(data[3], points[3]);
}