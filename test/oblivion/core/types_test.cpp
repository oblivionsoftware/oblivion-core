/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/types.h>

namespace oblivion {

/*****************************************************************************/

TEST(TypesTest, Sizes) {
    EXPECT_EQ(1, sizeof(int8));
    EXPECT_EQ(1, sizeof(uint8));
    EXPECT_EQ(2, sizeof(int16));
    EXPECT_EQ(2, sizeof(uint16));
    EXPECT_EQ(4, sizeof(int32));
    EXPECT_EQ(4, sizeof(uint32));
    EXPECT_EQ(8, sizeof(int64));
    EXPECT_EQ(8, sizeof(uint64));
    EXPECT_EQ(4, sizeof(real32));
    EXPECT_EQ(8, sizeof(real64));
}

/*****************************************************************************/

}
