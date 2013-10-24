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

    virtual std::unique_ptr<VariantValue> clone() const = 0;

    virtual int32 intValue() const {
        OB_THROW("Unsupported Operation");
    }

    virtual real32 realValue() const {
        OB_THROW("Unsupported operation");
    }

    virtual std::string stringValue() const {
        OB_THROW("Unsupported operation");
    }

    virtual int32 size() const {
        OB_THROW("Unsupported operation");
    }

    virtual Variant& getAtIndex(int32 index) {
        OB_THROW("Unsupported operation");
    }

    virtual const Variant& getAtIndex(int32 index) const {
        OB_THROW("Unsupported operation");
    }

    virtual Variant& getAtKey(const std::string& key) {
        OB_THROW("Unsupported operation");
    }

    virtual void clear() {
        OB_THROW("Unsupported operation");
    }

    virtual void add(const Variant& variant) {
        OB_THROW("Unsupported operation");
    }

    virtual bool containsKey(const std::string& key) const {
        OB_THROW("Unsupported operation");
    }

};

/**
 * A null variant value.
 */
class NullValue : public VariantValue {

public:

    VariantType type() const override {
        return VariantType::Null;
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new NullValue());
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

    VariantType type() const override {
        return VariantType::Number;
    }

    int32 intValue() const override {
        return static_cast<int32>(value_);
    }

    real32 realValue() const override {
        return value_;
    }

    std::string stringValue() const override {
        return StringUtil::toString(value_);
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new NumberValue(value_));
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

    VariantType type() const override {
        return VariantType::String;
    }

    int32 intValue() const override {
        return StringUtil::parse<int32>(value_);
    }

    real32 realValue() const override {
        return StringUtil::parse<real32>(value_);
    }

    std::string stringValue() const override {
        return value_;
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new StringValue(value_));
    }

private:

    std::string value_;

};

/**
 * A vector value.
 */
class VectorValue : public VariantValue {

public:

    VectorValue() {
    }

    VectorValue(std::vector<Variant> value)
        : value_(std::move(value)) {
    }

    VariantType type() const {
        return VariantType::Vector;
    }

    int32 size() const override {
        return static_cast<int32>(value_.size());
    }

    Variant& getAtIndex(int32 index) override {
        return value_[index];
    }

    const Variant& getAtIndex(int32 index) const override {
        return value_[index];
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new VectorValue(value_));
    }

    void clear() override {
        value_.clear();
    }

    void add(const Variant& variant) override {
        value_.emplace_back(variant);
    }

private:

    std::vector<Variant> value_;

};

/**
 * A map value.
 */
class MapValue : public VariantValue {

public:

    MapValue() {
    }

    MapValue(std::map<std::string, Variant> value)
        : value_(std::move(value)) {
    }

    VariantType type() const override {
        return VariantType::Map;
    }

    int32 size() const override {
        return static_cast<int32>(value_.size());
    }

    Variant& getAtKey(const std::string& key) override {
        return value_[key];
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new MapValue(value_));
    }

    void clear() override {
        value_.clear();
    }

    bool containsKey(const std::string& key) const override {
        return value_.find(key) != value_.end();
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

Variant::Variant(const Variant& variant) 
    : value_(variant.value_->clone()) {
}

/*****************************************************************************/

Variant::Variant(Variant&& variant)
    : value_(std::move(variant.value_)) {
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

int32 Variant::size() const {
    return value_->size();
}

/*****************************************************************************/

Variant& Variant::operator[](int32 index) {
    return value_->getAtIndex(index);
}

/*****************************************************************************/

const Variant& Variant::operator[](int32 index) const {
    return value_->getAtIndex(index);
}

/*****************************************************************************/

Variant& Variant::operator[](const std::string& key) {
    return value_->getAtKey(key);
}

/*****************************************************************************/

Variant& Variant::operator =(const Variant& variant) {
    value_ = variant.value_->clone();
    return *this;
}

/*****************************************************************************/

Variant& Variant::operator =(Variant&& variant) {
    value_ = std::move(variant.value_);
    return *this;
}

/*****************************************************************************/

void Variant::clear() {
    value_->clear();
}

/*****************************************************************************/

void Variant::add(const Variant& variant) {
    value_->add(variant);
}

/*****************************************************************************/

bool Variant::containsKey(const std::string& key) const {
    return value_->containsKey(key);
}

/*****************************************************************************/

}
