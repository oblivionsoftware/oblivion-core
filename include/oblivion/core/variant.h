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

    private:

        std::unique_ptr<VariantValue> value_;

    };

}

#endif /* _OBLIVION_CORE_VARIANT_H_ */
