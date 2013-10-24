/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/variant.h>

namespace oblivion {

/*****************************************************************************/

TEST(VariantTest, Default) {
    Variant var;

    EXPECT_EQ(VariantType::Null, var.type());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);
}

/*****************************************************************************/

TEST(VariantTest, Integer) {
    Variant var(10);

    EXPECT_EQ(VariantType::Number, var.type());
    EXPECT_EQ(10, var.intValue());
    EXPECT_EQ(10, var.realValue());
    EXPECT_EQ("10", var.stringValue());
}

/*****************************************************************************/

TEST(VariantTest, Real) {
    Variant var(10.25f);

    EXPECT_EQ(VariantType::Number, var.type());
    EXPECT_EQ(10.25f, var.realValue());
    EXPECT_EQ(10, var.intValue());
    EXPECT_EQ("10.25", var.stringValue());
}

/*****************************************************************************/

TEST(VariantTest, String) {
    Variant var("Hello, World!");

    EXPECT_EQ(VariantType::String, var.type());
    EXPECT_EQ("Hello, World!", var.stringValue());
    EXPECT_EQ(0, var.intValue());
    EXPECT_EQ(0, var.realValue());

    Variant var2("10.25");
    EXPECT_EQ(VariantType::String, var2.type());
    EXPECT_EQ("10.25", var2.stringValue());
    EXPECT_EQ(10, var2.intValue());
    EXPECT_EQ(10.25, var2.realValue());
}

/*****************************************************************************/

TEST(VariantTest, Vector) {
    Variant var(VariantType::Vector);

    EXPECT_EQ(VariantType::Vector, var.type());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);

    var.add(1);
    var.add("2");
    var.add(3.14f);

    EXPECT_EQ(3, var.size());
    EXPECT_EQ(1, var[0].intValue());
    EXPECT_EQ(2, var[1].intValue());
    EXPECT_EQ(3, var[2].intValue());

    var.clear();
    EXPECT_EQ(0, var.size());
}

/*****************************************************************************/

TEST(VariantTest, Map) {
    Variant var(VariantType::Map);

    EXPECT_EQ(VariantType::Map, var.type());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);

    var["num1"] = 10;
    var["num2"] = 20;

    EXPECT_EQ(10, var["num1"].intValue());
    EXPECT_EQ(20, var["num2"].intValue());
    EXPECT_EQ(VariantType::Null, var["invalid"].type());

    EXPECT_EQ(3, var.size());
    EXPECT_TRUE(var.containsKey("num1"));
    EXPECT_TRUE(var.containsKey("invalid"));
    EXPECT_FALSE(var.containsKey("notreal"));

    var.clear();
    EXPECT_EQ(0, var.size());
}

/*****************************************************************************/

TEST(VariantTest, Copy) {
    Variant vec(VariantType::Vector);
    vec.add(1);
    vec.add(2);

    Variant vecCopy = vec;
    vecCopy.clear();

    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(0, vecCopy.size());
}

/*****************************************************************************/

}
