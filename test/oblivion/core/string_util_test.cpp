/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/string_util.h>

namespace oblivion {

/******************************************************************************/

TEST(StringUtilTest, Trim) {
    std::string a = "\n    a\t";
    std::string b = "b  \n  ";
    std::string c = "   c \t ";

    trim(a);
    EXPECT_EQ("a", a);

    trim(b);
    EXPECT_EQ("b", b);

    trim(c);
    EXPECT_EQ("c", c);
}    

/******************************************************************************/

TEST(StringUtilTest, ToCsv) {
    std::vector<std::string> values;

    EXPECT_EQ("", toCsv(values));

    values.push_back("a");
    EXPECT_EQ("a", toCsv(values));

    values.push_back("b");
    EXPECT_EQ("a, b", toCsv(values));

    values.push_back("c");
    EXPECT_EQ("a, b, c", toCsv(values));
}    

/******************************************************************************/

TEST(StringUtilTest, ToUpper) {
    EXPECT_EQ("TWEET", toUpper("Tweet"));
    EXPECT_EQ("", toUpper(""));
    EXPECT_EQ("TWEET", toUpper("TWEET"));
    EXPECT_EQ("ALL_UPPER_123", toUpper("all_upper_123"));
}   

/******************************************************************************/

TEST(StringUtilTest, ToLower) {
    EXPECT_EQ("tweet", toLower("Tweet"));
    EXPECT_EQ("", toLower(""));
    EXPECT_EQ("tweet", toLower("TWEET"));
    EXPECT_EQ("all_lower_123", toLower("ALL_LOWER_123"));
}    

/******************************************************************************/

TEST(StringUtilTest, CamelCaseToUnderscores) {
    EXPECT_EQ("", camelCaseToUnderscores(""));
    EXPECT_EQ("abc_123", camelCaseToUnderscores("abc_123"));
    EXPECT_EQ("first_name", camelCaseToUnderscores("firstName"));
    EXPECT_EQ("uuid", camelCaseToUnderscores("UUID"));
    EXPECT_EQ("jpg_thumb", camelCaseToUnderscores("JPGThumb"));
    EXPECT_EQ("jpg_thumb", camelCaseToUnderscores("JPG_Thumb"));
}  

/******************************************************************************/

TEST(StringUtilTest, ToString) {
    EXPECT_EQ("", toString(""));
    EXPECT_EQ("true", toString(true));
    EXPECT_EQ("false", toString(false));
    EXPECT_EQ("342", toString(342));
    EXPECT_EQ("-342", toString(-342));
    EXPECT_EQ("asdf", toString("asdf"));
    EXPECT_EQ("asdf asdf", toString("asdf asdf"));
}    

/******************************************************************************/

TEST(StringUtilTest, FromString) {
    EXPECT_EQ("", fromString<std::string>(""));
    EXPECT_TRUE(fromString<bool>("true"));
    EXPECT_FALSE(fromString<bool>("false"));
    EXPECT_EQ(342, fromString<int>("342"));
    EXPECT_EQ(-342, fromString<int>("-342"));
    EXPECT_EQ("asdf", fromString<std::string>("asdf"));
    EXPECT_EQ("asdf asdf", fromString<std::string>("asdf asdf"));
}  

/******************************************************************************/

TEST(StringUtilTest, Contains) {
    EXPECT_TRUE(contains("1234", "1"));
    EXPECT_FALSE(contains("1234", "5"));
    EXPECT_FALSE(contains("", "a"));
    EXPECT_TRUE(contains("", ""));
} 

/******************************************************************************/

TEST(StringUtilTest, StartsWith) {
    EXPECT_TRUE(startsWith("1234", "1"));
    EXPECT_TRUE(startsWith("1234", "12"));
    EXPECT_FALSE(startsWith("1234", "4"));
    EXPECT_FALSE(startsWith("1234", "34"));
    EXPECT_TRUE(startsWith("1234", ""));
    EXPECT_TRUE(startsWith("", ""));
}  

/******************************************************************************/

TEST(StringUtilTest, EndsWith) {
    EXPECT_TRUE(endsWith("1234", "4"));
    EXPECT_TRUE(endsWith("1234", "34"));
    EXPECT_FALSE(endsWith("1234", "2"));
    EXPECT_FALSE(endsWith("1234", "1"));
    EXPECT_TRUE(endsWith("1234", ""));
    EXPECT_TRUE(endsWith("", ""));
}    

/******************************************************************************/

TEST(StringUtilTest, Format) {
    EXPECT_EQ("3 blind mice", formatString("%d blind mice", 3));
}    


/******************************************************************************/

}
