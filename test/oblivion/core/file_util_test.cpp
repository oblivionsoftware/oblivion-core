/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/algorithm.h>
#include <oblivion/core/exception.h>
#include <oblivion/core/file.h>
#include <oblivion/core/file_util.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

TEST(FileUtilTest, Exists) {
    EXPECT_FALSE(FileUtil::exists("notreal.txt"));

    {
        File file("test_exists.txt", "w");
    }

    EXPECT_TRUE(FileUtil::exists("test_exists.txt"));

    FileUtil::remove("test_exists.txt");
}

/*****************************************************************************/

TEST(FileUtilTest, Remove) {
    EXPECT_THROW(FileUtil::remove("notreal.txt"), Exception);

    {
        File testFile("test_delete.txt", "w");
    }

    EXPECT_TRUE(FileUtil::exists("test_delete.txt"));

    FileUtil::remove("test_delete.txt");

    EXPECT_FALSE(FileUtil::exists("test_delete.txt"));
}

/*****************************************************************************/

TEST(FileUtilTest, Directory) {
    if (!FileUtil::isDirectory("asdf")) {
        FileUtil::createDirectory("asdf");
    }

    EXPECT_TRUE(FileUtil::isDirectory("asdf"));

    {
        File testFile("test_dir.txt", "w");
    }

    EXPECT_TRUE(FileUtil::exists("test_dir.txt"));
    EXPECT_FALSE(FileUtil::isDirectory("test_dir.txt"));

    FileUtil::remove("test_dir.txt");
}

/*****************************************************************************/

TEST(FileUtilTest, Extension) {
    EXPECT_EQ(".exe", FileUtil::getExtension("oblivion.exe"));
    EXPECT_EQ("", FileUtil::getExtension("no_extension"));
    EXPECT_EQ(".tar.gz", FileUtil::getExtension("test.tar.gz"));
    EXPECT_EQ(".tar.gz", FileUtil::getExtension("./house.cards/test.tar.gz"));
    EXPECT_EQ(".tar.gz", FileUtil::getExtension(".\\house.cards\\test.tar.gz"));
}

/*****************************************************************************/

TEST(FileUtilTest, BaseName) {
    EXPECT_EQ("oblivion", FileUtil::getBaseName("oblivion.exe"));
    EXPECT_EQ("no_extension", FileUtil::getBaseName("no_extension"));
    EXPECT_EQ("test", FileUtil::getBaseName("test.tar.gz"));
    EXPECT_EQ("oblivion", FileUtil::getBaseName("/home/jeff/oblivion.exe"));
    EXPECT_EQ("oblivion", FileUtil::getBaseName("C:\\Users\\Jeff\\oblivion.tar.gz"));
    EXPECT_EQ("oblivion", FileUtil::getBaseName("./house.cards/oblivion.tar.gz"));
}

/*****************************************************************************/

TEST(FileUtilTest, FileName) {
    EXPECT_EQ("oblivion.exe", FileUtil::getFileName("oblivion.exe"));
    EXPECT_EQ("no_extension", FileUtil::getFileName("no_extension"));
    EXPECT_EQ("test.tar.gz", FileUtil::getFileName("test.tar.gz"));
    EXPECT_EQ("oblivion.exe", FileUtil::getFileName("/home/jeff/oblivion.exe"));
    EXPECT_EQ("oblivion.tar.gz", FileUtil::getFileName("C:\\Users\\Jeff\\oblivion.tar.gz"));
    EXPECT_EQ("oblivion.tar.gz", FileUtil::getFileName("./house.cards/oblivion.tar.gz"));
    EXPECT_EQ("test", FileUtil::getFileName("/home/jeff/test/"));
    EXPECT_EQ("test", FileUtil::getFileName("C:\\Users\\test\\"));
}

/*****************************************************************************/

TEST(FileUtilTest, ListFiles) {
    {
        File file("sample.txt", "wb");
    }

    auto files = FileUtil::listFiles(".");

    bool found = false;
    for (auto& file : files) {
        if (endsWith(file, "sample.txt")) {
            found = true;
        }
    }

    EXPECT_TRUE(found);

    FileUtil::remove("sample.txt");
}

/*****************************************************************************/

}
