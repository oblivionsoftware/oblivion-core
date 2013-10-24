/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/variant.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

/**
 * Interface for variant values.
 */
class VariantValue {

public:

    VariantValue() { }
    virtual ~VariantValue() { }

    virtual VariantType type() const = 0;

    virtual int32 intValue() const = 0;

    virtual real32 realValue() const = 0;

    virtual std::string stringValue() const = 0;

};

/**
 * A null variant value.
 */
class NullValue : public VariantValue {

public:

    VariantType type() const {
        return VariantType::Null;
    }

    int32 intValue() const {
        OB_THROW("Variant is null");
    }

    real32 realValue() const {
        OB_THROW("Variant is null");
    }

    std::string stringValue() const {
        OB_THROW("Variant is null");
    }

};

/**
 * A numeric value.
 */
class NumberValue : public VariantValue {

public:

    NumberValue(real32 value = 0) 
        : value_(value) {
    }

    VariantType type() const {
        return VariantType::Number;
    }

    int32 intValue() const {
        return static_cast<int32>(value_);
    }

    real32 realValue() const {
        return value_;
    }

    std::string stringValue() const {
        return StringUtil::toString(value_);
    }

private:

    real32 value_;

};

/**
 * A string value.
 */
class StringValue : public VariantValue {

public:

    StringValue() {
    }

    StringValue(std::string value) 
        : value_(std::move(value)) {
    }

    VariantType type() const {
        return VariantType::String;
    }

    int32 intValue() const {
        return StringUtil::parse<int32>(value_);
    }

    real32 realValue() const {
        return StringUtil::parse<real32>(value_);
    }

    std::string stringValue() const {
        return value_;
    }


private:

    std::string value_;

};

/**
 * A vector value.
 */
class VectorValue : public VariantValue {

public:

    VariantType type() const {
        return VariantType::Vector;
    }

    int32 intValue() const {
        OB_THROW("Cannot convert vector to int");
    }

    real32 realValue() const {
        OB_THROW("Cannot convert vector to real");
    }

    std::string stringValue() const {
        OB_NOT_IMPLEMENTED;
    }

private:

    std::vector<Variant> value_;

};

/**
 * A map value.
 */
class MapValue : public VariantValue {

public:

    VariantType type() const {
        return VariantType::Map;
    }

    int32 intValue() const {
        OB_THROW("Cannot convert map to int");
    }

    real32 realValue() const {
        OB_THROW("Cannot convert map to real");
    }

    std::string stringValue() const {
        OB_NOT_IMPLEMENTED;
    }

private:

    std::map<std::string, Variant> value_;

};

/*****************************************************************************/

Variant::Variant(VariantType type) {
    switch (type) {
    case VariantType::Number:
        value_.reset(new NumberValue());
        break;
    case VariantType::String:
        value_.reset(new StringValue());
    case VariantType::Vector:
        value_.reset(new VectorValue());
        break;
    case VariantType::Map:
        value_.reset(new MapValue());
        break;
    case VariantType::Null:
        value_.reset(new NullValue());
        break;
    } 
}

/*****************************************************************************/

Variant::Variant(int32 value) {
    value_.reset(new NumberValue(static_cast<real32>(value)));
}

/*****************************************************************************/

Variant::Variant(real32 value) {
    value_.reset(new NumberValue(value));
}

/*****************************************************************************/

Variant::Variant(const char* value) {
    value_.reset(new StringValue(value));
}

/*****************************************************************************/

Variant::Variant(const std::string& value) {
    value_.reset(new StringValue(value));
}

/*****************************************************************************/

Variant::~Variant() {
}

/*****************************************************************************/

VariantType Variant::type() const {
    return value_->type();
}

/*****************************************************************************/

int32 Variant::intValue() const {
    return value_->intValue();
}

/*****************************************************************************/

real32 Variant::realValue() const {
    return value_->realValue();
}

/*****************************************************************************/

std::string Variant::stringValue() const {
    return value_->stringValue();
}

/*****************************************************************************/

}
