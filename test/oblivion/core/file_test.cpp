/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/file.h>
#include <oblivion/core/file_util.h>

namespace oblivion {

struct TestData {
    int32 a;
    int32 b;
    int32 c;
};

/*****************************************************************************/

TEST(FileTest, ReadWrite) {
    EXPECT_THROW(File("notreal.txt", "rb"), Exception);

    TestData writeData;
    writeData.a = 1;
    writeData.b = 2;
    writeData.c = 3;

    {
        File outFile("test.txt", "wb");
        outFile.write(sizeof(TestData), &writeData);
    }

    TestData readData;

    {
        File inFile("test.txt", "rb");
        EXPECT_EQ(sizeof(TestData), inFile.size());
        inFile.read(sizeof(TestData), &readData);
    }

    EXPECT_EQ(readData.a, writeData.a);
    EXPECT_EQ(readData.b, writeData.b);
    EXPECT_EQ(readData.c, writeData.c);

    FileUtil::remove("test.txt");
}

/*****************************************************************************/

}
