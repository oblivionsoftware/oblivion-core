/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/types.h>

namespace oblivion {

/*****************************************************************************/

TEST(TypesTest, Sizes) {
    EXPECT_EQ(1u, sizeof(int8));
    EXPECT_EQ(1u, sizeof(uint8));
    EXPECT_EQ(2u, sizeof(int16));
    EXPECT_EQ(2u, sizeof(uint16));
    EXPECT_EQ(4u, sizeof(int32));
    EXPECT_EQ(4u, sizeof(uint32));
    EXPECT_EQ(8u, sizeof(int64));
    EXPECT_EQ(8u, sizeof(uint64));
    EXPECT_EQ(4u, sizeof(real32));
    EXPECT_EQ(8u, sizeof(real64));
}

/*****************************************************************************/

}
