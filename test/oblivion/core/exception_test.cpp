/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

TEST(ExceptionTest, Message) {
    int32 line;

    try {
        line = __LINE__;
        OB_THROW("Sample Message");
    } catch (Exception& ex) {
        EXPECT_EQ("Sample Message", ex.message());
        EXPECT_TRUE(endsWith(ex.file(), "exception_test.cpp"));
        EXPECT_TRUE(contains(ex.function(), "Message"));
        EXPECT_EQ(line + 1, ex.line());
        EXPECT_TRUE(contains(ex.what(), ex.message()));
        EXPECT_TRUE(contains(ex.what(), ex.file()));
        EXPECT_TRUE(contains(ex.what(), ex.function()));
        EXPECT_TRUE(contains(ex.what(), toString(ex.line())));
    }
}

/*****************************************************************************/

TEST(ExceptionTest, BaseMessage) {
    int32 line;

    try {
        line = __LINE__;
        OB_THROW("Sample Message");
    } catch (std::exception& ex) {
        EXPECT_TRUE(contains(ex.what(), "Sample Message"));
        EXPECT_TRUE(contains(ex.what(), "exception_test.cpp"));
        EXPECT_TRUE(contains(ex.what(), "BaseMessage"));
        EXPECT_TRUE(contains(ex.what(), toString(line + 1)));
    }
}

/*****************************************************************************/

}
