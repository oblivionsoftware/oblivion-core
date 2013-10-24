/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/variant.h>

#include <json/json.h>

#include <oblivion/core/algorithm.h>
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

    virtual real64 realValue() const {
        OB_THROW("Unsupported operation");
    }

    virtual std::string stringValue() const {
        OB_THROW("Unsupported operation");
    }

    virtual bool boolValue() const {
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

    virtual const Variant& getAtKey(const std::string& key) const {
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

    virtual std::vector<std::string> mapKeys() const {
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

    std::unique_ptr<VariantValue> clone() const override {
        return std::unique_ptr<VariantValue>(new NullValue());
    }

};

/**
 * A boolean value.
 */
class BoolValue : public VariantValue {

public:

    BoolValue(bool value = false) 
        : value_(value) {
    }

    VariantType type() const override {
        return VariantType::Bool;
    }

    int32 intValue() const override {
        return value_ ? 1 : 0;
    }

    std::string stringValue() const override {
        return value_ ? "true" : "false";
    }

    bool boolValue() const override {
        return value_;
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new BoolValue(value_));
    }

private:

    bool value_;

};

/**
 * A numeric integer value.
 */
class IntValue : public VariantValue {

public:

    IntValue(int32 value = 0) 
        : value_(value) {
    }

    VariantType type() const override {
        return VariantType::Integer;
    }

    int32 intValue() const override {
        return value_;
    }

    real64 realValue() const override {
        return value_;
    }

    std::string stringValue() const override {
        return StringUtil::toString(value_);
    }

    bool boolValue() const override {
        return value_ != 0;
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new IntValue(value_));
    }

private:

    int32 value_;

};

/**
 * A numeric real value.
 */
class RealValue : public VariantValue {

public:

    RealValue(real64 value = 0) 
        : value_(value) {
    }

    VariantType type() const override {
        return VariantType::Real;
    }

    int32 intValue() const override {
        return static_cast<int32>(value_);
    }

    real64 realValue() const override {
        return value_;
    }

    std::string stringValue() const override {
        return StringUtil::toString(value_);
    }

    std::unique_ptr<VariantValue> clone() const {
        return std::unique_ptr<VariantValue>(new RealValue(value_));
    }

private:

    real64 value_;

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

    real64 realValue() const override {
        return StringUtil::parse<real64>(value_);
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
 * An array value.
 */
class ArrayValue : public VariantValue {

public:

    ArrayValue() {
    }

    ArrayValue(std::vector<Variant> value)
        : value_(std::move(value)) {
    }

    VariantType type() const {
        return VariantType::Array;
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
        return std::unique_ptr<VariantValue>(new ArrayValue(value_));
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

    const Variant& getAtKey(const std::string& key) const override {
        auto itr = value_.find(key);

        if (itr == value_.end()) {
            OB_THROW("Key not found: " + key);
        }

        return itr->second;
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

    std::vector<std::string> mapKeys() const override {
        std::vector<std::string> result;
        map_keys(value_, std::back_inserter(result));

        return result;
    }

private:

    std::map<std::string, Variant> value_;

};

/*****************************************************************************/

Variant::Variant(VariantType type) {
    switch (type) {
    case VariantType::Integer:
        value_.reset(new IntValue());
        break;
    case VariantType::Real:
        value_.reset(new RealValue());
        break;
    case VariantType::Bool:
        value_.reset(new BoolValue());
        break;
    case VariantType::String:
        value_.reset(new StringValue());
    case VariantType::Array:
        value_.reset(new ArrayValue());
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
    value_.reset(new IntValue(value));
}

/*****************************************************************************/

Variant::Variant(real64 value) {
    value_.reset(new RealValue(value));
}

/*****************************************************************************/

Variant::Variant(bool value) {
    value_.reset(new BoolValue(value));
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

real64 Variant::realValue() const {
    return value_->realValue();
}

/*****************************************************************************/

std::string Variant::stringValue() const {
    return value_->stringValue();
}

/*****************************************************************************/

bool Variant::boolValue() const {
    return value_->boolValue();
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

const Variant& Variant::operator[](const std::string& key) const {
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

std::vector<std::string> Variant::mapKeys() const {
    return value_->mapKeys();
}

/*****************************************************************************/

static Json::Value toJsonValue(const Variant& variant) {
    switch (variant.type()) {
    case VariantType::Null:
        return Json::Value();
    case VariantType::Integer:
        return variant.intValue();
    case VariantType::Real:
        return variant.realValue();
    case VariantType::String:
        return variant.stringValue();
    case VariantType::Bool:
        return variant.boolValue();
    case VariantType::Array: {
        Json::Value result(Json::arrayValue);
        for (auto i = 0; i < variant.size(); ++i) {
            result.append(toJsonValue(variant[i]));
        }

        return result;
    }
    case VariantType::Map: {
        Json::Value result(Json::objectValue);
        for (auto& key : variant.mapKeys()) {
            result[key] = toJsonValue(variant[key]);
        }

        return result;
    }
    default:
        OB_THROW("Unsupported variant type");
    }
}

/*****************************************************************************/

static Variant fromJsonValue(const Json::Value& value) {
    switch (value.type()) {
    case Json::nullValue:
        return Variant();
    case Json::intValue:
        return value.asInt();
    case Json::uintValue:
        return value.asInt();
    case Json::realValue:
        return value.asDouble();
    case Json::stringValue:
        return value.asString();
    case Json::booleanValue:
        return value.asBool();
    case Json::arrayValue: {
        Variant result(VariantType::Array);
        for (auto i = 0u; i < value.size(); ++i) {
            result.add(fromJsonValue(value[i]));
        }

        return result;
    }
    case Json::objectValue: {
        Variant result(VariantType::Map);
        for (auto& name : value.getMemberNames()) {
            result[name] = fromJsonValue(value[name]);
        }

        return result;
    }
    default:
        OB_THROW("Unsupported value type");
    }
}

/*****************************************************************************/

std::string Variant::toJson() const {
    Json::FastWriter writer;
    
    auto result = writer.write(toJsonValue(*this));
    StringUtil::trim(result);

    return result;
}

/*****************************************************************************/

Variant Variant::parseJson(const std::string& jsonString) {
    Json::Reader reader;
    Json::Value value;

    if (!reader.parse(jsonString, value)) {
        OB_THROW("Unable to parse JSON: " + reader.getFormattedErrorMessages());
    }

    return fromJsonValue(value);
}

/*****************************************************************************/

}
