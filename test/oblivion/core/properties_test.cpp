/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/file_util.h>
#include <oblivion/core/properties.h>

namespace oblivion {

/*****************************************************************************/

TEST(PropertiesTest, Get) {
    Properties props;
    props.set("name", "Jeff");
    props.set("age", 28);

    EXPECT_EQ("Jeff", props.get<std::string>("name"));
    EXPECT_EQ(28, props.get<int32>("age"));
}

/*****************************************************************************/

TEST(PropertiesTest, SaveLoadConstructor) {
    Properties p1;
    p1.set("name", "Jeff");
    p1.set("age", 28);
    p1.save("test.properties");

    Properties p2("test.properties");
    EXPECT_EQ("Jeff", p2.get<std::string>("name"));
    EXPECT_EQ(28, p2.get<int32>("age"));

    FileUtil::remove("test.properties");
}

/*****************************************************************************/

TEST(PropertiesTest, SaveLoad) {
    Properties p1;
    p1.set("name", "Jeff");
    p1.set("age", 28);
    p1.save("test.properties");

    Properties p2;
    p2.load("test.properties");
    EXPECT_EQ("Jeff", p2.get<std::string>("name"));
    EXPECT_EQ(28, p2.get<int32>("age"));

    EXPECT_THROW(p2.load("notreal.properties"), Exception);

    FileUtil::remove("test.properties");
}

/*****************************************************************************/

TEST(PropertiesTest, Iterable) {
    Properties p1;
    p1.set("name", "Jeff");
    p1.set("age", "28");

    int32 count = 0;
    std::string names;

    for (auto& entry: p1) {
        ++count;
        names += entry.first;
    }

    EXPECT_EQ(2, count);
    EXPECT_TRUE(StringUtil::contains(names, "name"));
    EXPECT_TRUE(StringUtil::contains(names, "age"));
}


/*****************************************************************************/

TEST(PropertiesTest, Clear) {
    Properties p1;
    p1.set("name", "Jeff");
    p1.set("age", "28");

    EXPECT_EQ(2, p1.size());
    EXPECT_FALSE(p1.empty());

    p1.clear();

    EXPECT_EQ(0, p1.size());
    EXPECT_TRUE(p1.empty());
}

/*****************************************************************************/

}
