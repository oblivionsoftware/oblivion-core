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
        Integer,
        Real,
        Bool,
        String,
        Array,
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
        Variant(real64 value);

        /**
         * Constructs a boolean variant with the specified value.
         * @param value The bool value.
         */
        Variant(bool value);

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
         * Move constructor.
         * @param variant The variant to move.
         */
        Variant(Variant&& variant);

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
        real64 realValue() const;

        /**
         * Gets the boolean value of this variant.
         * @return The boolean value.
         */
        bool boolValue() const;

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
         * Gets a reference to the variant at the specified key. This
         * method only works on VariantType::Map.
         * @param key The to retrieve.
         * @return A reference to the variant.
         */
        const Variant& operator[](const std::string& key) const;

        /**
         * Copy assignment.
         * @param variant The variant to copy.
         * @return A reference to this.
         */
        Variant& operator =(const Variant& variant);

        /**
         * Move assignment.
         * @param variant The variant to move.
         * @return A reference to this.
         */
        Variant& operator =(Variant&& variant);

        /**
         * Removes all elements of a container.
         */
        void clear();

        /**
         * Adds an element to this Variant. Only supported by VariantType::Vector
         * @param variant The variant to add.
         */
        void add(const Variant& variant);

        /**
         * Gets whether or not this variant contains the specified key. Only supported
         * by VariantType::Map.
         * @param key The key to check.
         * @return True if the variant contains the specified key, false otherwise.
         */
        bool containsKey(const std::string& key) const;

        /**
         * Gets the keys for the map. Only supported by VAriantType::Map.
         * @return The set of map keys.
         */
        std::vector<std::string> mapKeys() const;

        /**
         * Gets the JSON value of this Variant.
         * @return The JSON value.
         */
        std::string toJson() const;

        /**
         * Parses a JSON string.
         * @param jsonString the input JSON string.
         * @return The equivalent variant.
         */
        static Variant parseJson(const std::string& jsonString);

    private:

        std::unique_ptr<VariantValue> value_;

    };

}

#endif /* _OBLIVION_CORE_VARIANT_H_ */
