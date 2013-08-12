/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/variant.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

Variant::Variant(VariantType type)
    : type_(type) {
}

/*****************************************************************************/

Variant::Variant(int32 value)
    : type_(VariantType::Integer),
      int_(value) {
}

/*****************************************************************************/

Variant::Variant(real32 value) 
    : type_(VariantType::Real),
      real_(value) {
}

/*****************************************************************************/

Variant::Variant(const std::string& value)
    : type_(VariantType::String),
      string_(value) {
}

/*****************************************************************************/

VariantType Variant::type() const {
    return type_;
}

/*****************************************************************************/

int32 Variant::intValue() const {
    checkType(VariantType::Integer);

    return int_;
}

/*****************************************************************************/

real32 Variant::realValue() const {
    checkType(VariantType::Real);

    return real_;
}

/*****************************************************************************/

const std::string& Variant::stringValue() const {
    checkType(VariantType::String);

    return string_;
}

/*****************************************************************************/

void Variant::checkType(VariantType type) const {
    if (type_ != type) {
        OB_THROW("Type does not match");
    }
}

/*****************************************************************************/

}
