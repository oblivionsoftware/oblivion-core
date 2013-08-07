/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_STRING_UTIL_H_
#define _OBLIVION_CORE_STRING_UTIL_H_

#include <sstream>
#include <string>
#include <vector>

#include <oblivion/core/base.h>

namespace oblivion {

    /**
     * Escapes any quote characters in the string.
     * @param text The string to escape.
     * @return The escaped string.
     */
    OB_CORE_API std::string escapeQuotes(const std::string& text); 

    /**
     * Trims the string in-place.
     * @param text The string to trim.
     */
    OB_CORE_API void trim(std::string& text);

    /**
     * Decodes a URL-encoded string.
     * @param input The input string.
     * @return The decoded string.
     */
    OB_CORE_API std::string urlDecode(const std::string& input);

    /**
     * Gets the upper-case version of the input string.
     * @param input The input string.
     * @return The upper-case version.
     */
    OB_CORE_API std::string toUpper(std::string input);

    /**
     * Gets the lower-case version of the input string.
     * @param input The input string.
     * @return The lower-case version.
     */
    OB_CORE_API std::string toLower(std::string input);
  
    /**
     * Converts a camel case string to a lowercase string separated by underscores.
     * @param input The input string.
     * @return The converted string.
     */
    OB_CORE_API std::string camelCaseToUnderscores(const std::string& input);

    /**
     * Converts from a value to a string.
     * @param value The value to convert.
     * @return The string representation of value.
     */
    template <typename T>
    std::string toString(const T& value);

    /**
     * Specialization of bool -> string
     * that returns "true" or "false"
     */
    template <>
    OB_CORE_API std::string toString(const bool& value);

    /**
     * Specialization of pair -> string
     */
    template <typename K, typename V>
    std::string toString(const std::pair<K,V>& value);

    /**
     * Gets a value from a strong.
     * @param stringValue The string value.   
     * @return The value read from the string.
     */
    template <typename T>
    T fromString(const std::string& stringValue);

    /**
     * Specialization of string -> bool that
     * converts "true" to true and everything else to false.
     */
    template <>
    OB_CORE_API bool fromString(const std::string& stringValue);

    /**
     * Specialization of string -> string that simply returns
     * the string.
     */
    template <>
    OB_CORE_API std::string fromString(const std::string& stringValue);

    /**
     * Converts an iterator range to CSV.
     * @param begin The starting iterator.
     * @param end The ending iterator.
     * @return The CSV string.
     */
    template <typename Iterator>
    std::string toCsv(Iterator begin, Iterator end);

    /**
     * Converts a container to CSV.
     * @param container The container to convert.
     * @return The CSV string.
     */
    template <typename Container>
    std::string toCsv(const Container& container);

}

#include <oblivion/core/string_util_inl.h>

#endif /* _OBLIVION_CORE_STRING_UTIL_H_ */
