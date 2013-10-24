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

    EXPECT_EQ(VariantType::Integer, var.type());
    EXPECT_EQ(10, var.intValue());
    EXPECT_EQ(10, var.realValue());
    EXPECT_EQ("10", var.stringValue());
}

/*****************************************************************************/

TEST(VariantTest, Bool) {
    Variant var(true);

    EXPECT_EQ(VariantType::Bool, var.type());
    EXPECT_EQ(1, var.intValue());
    EXPECT_TRUE(var.boolValue());
    EXPECT_EQ("true", var.stringValue());

    var = false;
    EXPECT_EQ(VariantType::Bool, var.type());
    EXPECT_EQ(0, var.intValue());
    EXPECT_FALSE(var.boolValue());
    EXPECT_EQ("false", var.stringValue());    
}

/*****************************************************************************/

TEST(VariantTest, Real) {
    Variant var(10.25);

    EXPECT_EQ(VariantType::Real, var.type());
    EXPECT_EQ(10.25, var.realValue());
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

TEST(VariantTest, Array) {
    Variant var(VariantType::Array);

    EXPECT_EQ(VariantType::Array, var.type());
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
    Variant var(VariantType::Array);
    var.add(1);
    var.add(2);

    Variant varCopy = var;
    varCopy.clear();

    EXPECT_EQ(2, var.size());
    EXPECT_EQ(0, varCopy.size());
}

/*****************************************************************************/

TEST(VariantTest, ToJson) {
    Variant v;

    EXPECT_EQ("null", v.toJson());

    v = 3;
    EXPECT_EQ("3", v.toJson());

    v = 3.14;
    EXPECT_EQ("3.140", v.toJson());

    v = "Hello, World";
    EXPECT_EQ("\"Hello, World\"", v.toJson());

    v = true;
    EXPECT_EQ("true", v.toJson());

    v = false;
    EXPECT_EQ("false", v.toJson());

    v = Variant(VariantType::Array);
    v.add(1);
    v.add("test");
    v.add(4);

    EXPECT_EQ("[1,\"test\",4]", v.toJson());

    Variant mapVar(VariantType::Map);

    EXPECT_EQ("{}", mapVar.toJson());

    mapVar["a"] = 2;
    mapVar["b"] = "name";
    mapVar["c"] = v;

    EXPECT_EQ("{\"a\":2,\"b\":\"name\",\"c\":[1,\"test\",4]}", mapVar.toJson());
}

/*****************************************************************************/

TEST(VariantTest, ParseJson) {
    Variant v = Variant::parseJson("null");
    EXPECT_EQ(VariantType::Null, v.type());

    v = Variant::parseJson("3");
    EXPECT_EQ(VariantType::Integer, v.type());
    EXPECT_EQ(3, v.intValue());

    v = Variant::parseJson("3.14");
    EXPECT_EQ(VariantType::Real, v.type());
    EXPECT_EQ(3.14, v.realValue());

    v = Variant::parseJson("\"Hello, World\"");
    EXPECT_EQ(VariantType::String, v.type());
    EXPECT_EQ("Hello, World", v.stringValue());

    v = Variant::parseJson("true");
    EXPECT_EQ(VariantType::Bool, v.type());
    EXPECT_TRUE(v.boolValue());

    v = Variant::parseJson("false");
    EXPECT_EQ(VariantType::Bool, v.type());
    EXPECT_FALSE(v.boolValue());

    v = Variant::parseJson("[1,\"test\",4]");
    EXPECT_EQ(VariantType::Array, v.type());
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(1, v[0].intValue());
    EXPECT_EQ("test", v[1].stringValue());
    EXPECT_EQ(4, v[2].intValue());

    v = Variant::parseJson("{\"a\":2,\"b\":\"name\",\"c\":[1,\"test\",4]}");
    EXPECT_EQ(VariantType::Map, v.type());
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(2, v["a"].intValue());
    EXPECT_EQ("name", v["b"].stringValue());

    auto& c = v["c"];
    EXPECT_EQ(VariantType::Array, c.type());
    EXPECT_EQ(3, c.size());
    EXPECT_EQ(1, c[0].intValue());
    EXPECT_EQ("test", c[1].stringValue());
    EXPECT_EQ(4, c[2].intValue());

    EXPECT_THROW(Variant::parseJson("s;lkj45#$"), Exception);
}

/*****************************************************************************/

TEST(VariantTest, ToString) {
    Variant var(VariantType::Array);
    var.add(1);
    var.add(2);

    EXPECT_EQ("[1,2]", StringUtil::toString(var));
}

/*****************************************************************************/

TEST(VariantTest, Parse) {
    Variant var = StringUtil::parse<Variant>("[1,2]");
    EXPECT_EQ(VariantType::Array, var.type());
    EXPECT_EQ(1, var[0].intValue());
    EXPECT_EQ(2, var[1].intValue());
}

/*****************************************************************************/

}
