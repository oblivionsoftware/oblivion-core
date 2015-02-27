/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <sstream>

#include <oblivion/core/string_util.h>
#include <oblivion/core/timestamp.h>

namespace oblivion {

/*****************************************************************************/

TEST(TimestampTest, Format) {
    Timestamp timestamp;

    std::stringstream s1;
    s1 << timestamp;

    std::stringstream s2;
    timestamp.print(s2);

    EXPECT_EQ(s1.str(), s2.str());

    auto isoString = timestamp.iso8601();
    EXPECT_EQ(20u, isoString.size());
    EXPECT_TRUE(StringUtil::endsWith(isoString, "Z"));
}

/*****************************************************************************/

}
