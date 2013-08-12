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
    Variant var = 10;;

    EXPECT_EQ(VariantType::Integer, var.type());
    EXPECT_EQ(10, var.intValue());
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);
}

/*****************************************************************************/

TEST(VariantTest, Real) {
    Variant var = 10.0f;

    EXPECT_EQ(VariantType::Real, var.type());
    EXPECT_EQ(10.0f, var.realValue());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);
}

/*****************************************************************************/

TEST(VariantTest, String) {
    Variant var = "Hello, World!";

    EXPECT_EQ(VariantType::String, var.type());
    EXPECT_EQ("Hello, World!", var.stringValue());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
}

/*****************************************************************************/

TEST(VariantTest, Vector) {
    Variant var(VariantType::Vector);

    EXPECT_EQ(VariantType::Vector, var.type());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);
}

/*****************************************************************************/

TEST(VariantTest, Map) {
    Variant var(VariantType::Map);

    EXPECT_EQ(VariantType::Map, var.type());
    EXPECT_THROW(var.intValue(), Exception);
    EXPECT_THROW(var.realValue(), Exception);
    EXPECT_THROW(var.stringValue(), Exception);
}

/*****************************************************************************/

}
