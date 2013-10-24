/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_VARIANT_H_
#define _OBLIVION_CORE_VARIANT_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

namespace oblivion {

    /**
     * The possible types a variant holds.
     */
    enum class VariantType {
        Null,
        Number,
        String,
        Vector,
        Map
    };

    /**
     * Interface for variant values.
     */
    class VariantValue;

    /**
     * Variable that is able to hold one of several types.
     */
    class OB_CORE_API Variant {

    public:

        /**
         * Constructs a variant of the specified value.
         * @param type The type of this variant.
         */
        explicit Variant(VariantType type = VariantType::Null);

        /**
         * Constructs an integer variant with the specified value.
         * @param value The integer value.
         */
        Variant(int32 value);

        /**
         * Constructs a real variant with the specified value.
         * @param value The real value.
         */
        Variant(real32 value);

        /**
         * Constructs a string variant with the specified value.
         * @param value The string value.
         */
        Variant(const char* value);

        /**
         * Constructs a string variant with the specified value.
         * @param value The string value.
         */
        Variant(const std::string& value);

        /**
         * Copy constructor.
         * @param variant The variant to copy.
         */
        Variant(const Variant& variant);

        /**
         * Cleanup.
         */
        ~Variant();

        /**
         * Gets the type of this variant.
         * @return The type of this variant.
         */
        VariantType type() const;

        /**
         * Gets the integer value of this variant.
         * @return The integer value.
         */
        int32 intValue() const;

        /**
         * Gets the real value of this variant.
         * @return The real value.
         */
        real32 realValue() const;

        /**
         * Gets the string value of this variant.
         * @return The string value.
         */
        std::string stringValue() const;

        /**
         * Gets the size if this is an array or map.
         * @return The size.
         */
        int32 size() const;

        /**
         * Gets the variant at the specified index. This method only
         * works on VariantType::Vector.
         * @param index The index to access.
         * @return A reference to the variant.
         */
        Variant& operator[](int32 index);

        /**
         * Gets the variant at the specified index. This method only
         * works on VariantType::Vector.
         * @param index The index to access.
         * @return A const reference to the variant.
         */
        const Variant& operator[](int32 index) const;

        /**
         * Gets a reference to the variant at the specified key. This
         * method only works on VariantType::Map.
         * @param key The to retrieve.
         * @return A reference to the variant.
         */
        Variant& operator[](const std::string& key);

        /**
         * Copy assignment.
         * @param variant The variant to copy.
         * @return A reference to this.
         */
        Variant& operator =(const Variant& variant);

    private:

        std::unique_ptr<VariantValue> value_;

    };

}

#endif /* _OBLIVION_CORE_VARIANT_H_ */
