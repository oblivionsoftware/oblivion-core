/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <vector>

#include <oblivion/core/algorithm.h>
#include <oblivion/core/types.h>

namespace oblivion {

/******************************************************************************/

TEST(AlgorithmTest, ForEach) {
    std::vector<int32> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    int32 i = 0;
    for_each(v, [&](int value) {
        i += value;
    });

    EXPECT_EQ(6, i);
}

/******************************************************************************/

TEST(AlgorithmTest, FindIf) {
    std::vector<int32> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto itr = find_if(v, [](int value) {
        return value == 2;
    });

    EXPECT_NE(v.end(), itr);

    itr = find_if(v, [](int value) {
        return value == 10;
    });

    EXPECT_EQ(v.end(), itr);
}

/******************************************************************************/

TEST(AlgorithmTest, MapKeys) {
    std::map<int32, int32> m;
    m.insert(std::make_pair(1, 2));
    m.insert(std::make_pair(2, 4));
    m.insert(std::make_pair(3, 6));

    std::vector<int32> keys;
    map_keys(m, std::back_inserter(keys));

    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(1, keys[0]);
    EXPECT_EQ(2, keys[1]);
    EXPECT_EQ(3, keys[2]);
}

/******************************************************************************/

TEST(AlgorithmTest, MapValues) {
    std::map<int32, int32> m;
    m.insert(std::make_pair(1, 2));
    m.insert(std::make_pair(2, 4));
    m.insert(std::make_pair(3, 6));

    std::vector<int32> values;
    map_values(m, std::back_inserter(values));

    EXPECT_EQ(3, values.size());
    EXPECT_EQ(2, values[0]);
    EXPECT_EQ(4, values[1]);
    EXPECT_EQ(6, values[2]);
}

/******************************************************************************/

TEST(AlgorithmTest, Erase) {
    std::vector<int32> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    erase(v, 2);
    EXPECT_EQ(2, v.size());

    erase(v, 4);
    EXPECT_EQ(2, v.size());

    erase(v, 3);
    EXPECT_EQ(1, v.size());

    erase(v, 1);
    EXPECT_EQ(0, v.size());
}

/******************************************************************************/

TEST(AlgorithmTest, EraseIf) {
    std::vector<int32> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    erase_if(v, [](int v) {
        return v <= 2;
    });

    EXPECT_EQ(2, v.size());
    EXPECT_EQ(3, v[0]);
    EXPECT_EQ(4, v[1]);
}


/******************************************************************************/

TEST(AlgorithmTest, Contains) {
    std::vector<int32> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    EXPECT_TRUE(contains(v, 1));
    EXPECT_TRUE(contains(v, 2));
    EXPECT_FALSE(contains(v, 4));

    erase(v, 2);
    EXPECT_FALSE(contains(v, 2));
}

/******************************************************************************/

}
