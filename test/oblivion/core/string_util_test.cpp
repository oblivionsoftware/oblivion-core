/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/string_util.h>

namespace oblivion {

/******************************************************************************/

TEST(StringUtilTest, Trim) {
    std::string a = "\n    a\t";
    std::string b = "b  \n  ";
    std::string c = "   c \t ";

    StringUtil::trim(a);
    EXPECT_EQ("a", a);

    StringUtil::trim(b);
    EXPECT_EQ("b", b);

    StringUtil::trim(c);
    EXPECT_EQ("c", c);
}    

/******************************************************************************/

TEST(StringUtilTest, ToCsv) {
    std::vector<std::string> values;

    EXPECT_EQ("", StringUtil::toCsv(values));

    values.push_back("a");
    EXPECT_EQ("a", StringUtil::toCsv(values));

    values.push_back("b");
    EXPECT_EQ("a, b", StringUtil::toCsv(values));

    values.push_back("c");
    EXPECT_EQ("a, b, c", StringUtil::toCsv(values));
}    

/******************************************************************************/

TEST(StringUtilTest, ToUpper) {
    EXPECT_EQ("TWEET", StringUtil::toUpper("Tweet"));
    EXPECT_EQ("", StringUtil::toUpper(""));
    EXPECT_EQ("TWEET", StringUtil::toUpper("TWEET"));
    EXPECT_EQ("ALL_UPPER_123", StringUtil::toUpper("all_upper_123"));
}   

/******************************************************************************/

TEST(StringUtilTest, ToLower) {
    EXPECT_EQ("tweet", StringUtil::toLower("Tweet"));
    EXPECT_EQ("", StringUtil::toLower(""));
    EXPECT_EQ("tweet", StringUtil::toLower("TWEET"));
    EXPECT_EQ("all_lower_123", StringUtil::toLower("ALL_LOWER_123"));
}    

/******************************************************************************/

TEST(StringUtilTest, CamelCaseToUnderscores) {
    EXPECT_EQ("", StringUtil::camelCaseToUnderscores(""));
    EXPECT_EQ("abc_123", StringUtil::camelCaseToUnderscores("abc_123"));
    EXPECT_EQ("first_name", StringUtil::camelCaseToUnderscores("firstName"));
    EXPECT_EQ("uuid", StringUtil::camelCaseToUnderscores("UUID"));
    EXPECT_EQ("jpg_thumb", StringUtil::camelCaseToUnderscores("JPGThumb"));
    EXPECT_EQ("jpg_thumb", StringUtil::camelCaseToUnderscores("JPG_Thumb"));
}  

/******************************************************************************/

TEST(StringUtilTest, ToString) {
    EXPECT_EQ("", StringUtil::toString(""));
    EXPECT_EQ("true", StringUtil::toString(true));
    EXPECT_EQ("false", StringUtil::toString(false));
    EXPECT_EQ("342", StringUtil::toString(342));
    EXPECT_EQ("-342", StringUtil::toString(-342));
    EXPECT_EQ("asdf", StringUtil::toString("asdf"));
    EXPECT_EQ("asdf asdf", StringUtil::toString("asdf asdf"));
}    

/******************************************************************************/

TEST(StringUtilTest, FromString) {
    EXPECT_EQ("", StringUtil::parse<std::string>(""));
    EXPECT_TRUE(StringUtil::parse<bool>("true"));
    EXPECT_FALSE(StringUtil::parse<bool>("false"));
    EXPECT_EQ(342, StringUtil::parse<int>("342"));
    EXPECT_EQ(-342, StringUtil::parse<int>("-342"));
    EXPECT_EQ("asdf", StringUtil::parse<std::string>("asdf"));
    EXPECT_EQ("asdf asdf", StringUtil::parse<std::string>("asdf asdf"));
}  

/******************************************************************************/

TEST(StringUtilTest, Contains) {
    EXPECT_TRUE(StringUtil::contains("1234", "1"));
    EXPECT_FALSE(StringUtil::contains("1234", "5"));
    EXPECT_FALSE(StringUtil::contains("", "a"));
    EXPECT_TRUE(StringUtil::contains("", ""));
} 

/******************************************************************************/

TEST(StringUtilTest, StartsWith) {
    EXPECT_TRUE(StringUtil::startsWith("1234", "1"));
    EXPECT_TRUE(StringUtil::startsWith("1234", "12"));
    EXPECT_FALSE(StringUtil::startsWith("1234", "4"));
    EXPECT_FALSE(StringUtil::startsWith("1234", "34"));
    EXPECT_TRUE(StringUtil::startsWith("1234", ""));
    EXPECT_TRUE(StringUtil::startsWith("", ""));
}  

/******************************************************************************/

TEST(StringUtilTest, EndsWith) {
    EXPECT_TRUE(StringUtil::endsWith("1234", "4"));
    EXPECT_TRUE(StringUtil::endsWith("1234", "34"));
    EXPECT_FALSE(StringUtil::endsWith("1234", "2"));
    EXPECT_FALSE(StringUtil::endsWith("1234", "1"));
    EXPECT_TRUE(StringUtil::endsWith("1234", ""));
    EXPECT_TRUE(StringUtil::endsWith("", ""));
}    

/******************************************************************************/

TEST(StringUtilTest, Format) {
    EXPECT_EQ("3 blind mice", StringUtil::formatString("%d blind mice", 3));
}    


/******************************************************************************/

}
