#include <gtest/gtest.h>

#include "Memory.h"

TEST(SetGetRGBTest, BasicAssertions)
{
    unsigned char* data = new unsigned char[640*480*3];
    memset(data, 0, (int)sizeof(data));

    MHV::Memory m{640,480};
    m.setRGBData(data);

    EXPECT_EQ(sizeof(data), sizeof(m.getRGBData()));
    delete[] data;
}
