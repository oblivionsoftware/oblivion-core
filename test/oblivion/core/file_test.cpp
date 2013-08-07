/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/file.h>

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

    File outFile("test.txt", "wb");
    outFile.write(sizeof(TestData), &writeData);
    outFile.close();

    TestData readData;

    File inFile("test.txt", "rb");
    EXPECT_EQ(sizeof(TestData), inFile.size());
    inFile.read(sizeof(TestData), &readData);
    inFile.close();

    EXPECT_EQ(readData.a, writeData.a);
    EXPECT_EQ(readData.b, writeData.b);
    EXPECT_EQ(readData.c, writeData.c);
}

/*****************************************************************************/

TEST(FileTest, Exists) {
    EXPECT_FALSE(File::exists("notreal.txt"));

    File file("test_exists.txt", "w");
    file.close();

    EXPECT_TRUE(File::exists("test_exists.txt"));
}

/*****************************************************************************/

TEST(FileTest, Remove) {
    EXPECT_THROW(File::remove("notreal.txt"), Exception);

    File testFile("test_delete.txt", "w");
    testFile.close();

    EXPECT_TRUE(File::exists("test_delete.txt"));

    File::remove("test_delete.txt");

    EXPECT_FALSE(File::exists("test_delete.txt"));
}

/*****************************************************************************/

}
