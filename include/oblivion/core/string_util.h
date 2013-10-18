/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_STRING_UTIL_H_
#define _OBLIVION_CORE_STRING_UTIL_H_

#include <cstdarg>
#include <sstream>
#include <string>
#include <vector>

#include <oblivion/core/base.h>

namespace oblivion {

    /**
     * String utility functions.
     */
    class OB_CORE_API StringUtil {

    public:

        /**
         * Escapes any quote characters in the string.
         * @param text The string to escape.
         * @return The escaped string.
         */
        static std::string escapeQuotes(const std::string& text);

        /**
         * Trims the string in-place.
         * @param text The string to trim.
         */
        static void trim(std::string& text);

        /**
         * Decodes a URL-encoded string.
         * @param input The input string.
         * @return The decoded string.
         */
        static std::string urlDecode(const std::string& input);

        /**
         * Gets the upper-case version of the input string.
         * @param input The input string.
         * @return The upper-case version.
         */
        static std::string toUpper(std::string input);

        /**
         * Gets the lower-case version of the input string.
         * @param input The input string.
         * @return The lower-case version.
         */
        static std::string toLower(std::string input);

        /**
         * Converts a camel case string to a lowercase string separated by underscores.
         * @param input The input string.
         * @return The converted string.
         */
        static std::string camelCaseToUnderscores(const std::string& input);

        /**
         * Gets whether or not a string contains the specified substring.
         * @param input The input string.
         * @param search The string to search for.
         * @return True if the input string contains search, false otherwise.
         */
        static bool contains(const std::string& input, const std::string& search);

        /**
         * Gets whether or not a string starts with the specified substring.
         * @param input The input string.
         * @param search The string to check for.
         * @return True if the input string starts with the search string, false otherwise.
         */
        static bool startsWith(const std::string& input, const std::string& search);

        /**
         * Gets whether or not a string ends with the specified substring.
         * @param input The input string.
         * @param search The string to check for.
         * @return True if the input string ends with the search string, false otherwise.
         */
        static bool endsWith(const std::string& input, const std::string& search);

        /**
         * Formats a string using a printf style format string.
         * @param format The printf style format string.
         * @return The formatted string.
         */
        static std::string formatString(const char* format, ...);

        /**
         * Formats a string using a printf style format string using a variable argument list.
         * @param format The printf style format string.
         * @param args The variable argument list.
         */
        static std::string formatString(const char* format, va_list args);

        /**
         * Splits the specified text into tokens.
         * @param text The input text.
         * @param delimiter The delimiter
         * @param trimTokens Whether to trim the tokens or not.
         * @return The list of tokens.
         */
        static std::vector<std::string> split(const std::string& text, char delimiter, bool trimTokens = false);

        /**
         * Converts an iterator range to CSV.
         * @param begin The starting iterator.
         * @param end The ending iterator.
         * @return The CSV string.
         */
        template <typename Iterator>
        static std::string toCsv(Iterator begin, Iterator end);

        /**
         * Converts a container to CSV.
         * @param container The container to convert.
         * @return The CSV string.
         */
        template <typename Container>
        static std::string toCsv(const Container& container);

        /**
         * Converts from a value to a string.
         * @param value The value to convert.
         * @return The string representation of value.
         */
        template <typename T>
        static std::string toString(const T& value);

        /**
         * Specialization of pair -> string
         */
        template <typename K, typename V>
        static std::string toString(const std::pair<K,V>& value);

        /**
         * Specialization of vector to string.
         */
        template <typename T>
        static std::string toString(const std::vector<T>& value);

        /**
         * Gets a value from a strong.
         * @param stringValue The string value.
         * @return The value read from the string.
         */
        template <typename T>
        static T parse(const std::string& stringValue);

    };

    /**
     * Specialization of bool -> string
     * that returns "true" or "false"
     */
    template <>
    OB_CORE_API std::string StringUtil::toString(const bool& value);

    /**
     * Specialization of string -> bool that
     * converts "true" to true and everything else to false.
     */
    template <>
	OB_CORE_API bool StringUtil::parse(const std::string& stringValue);

    /**
     * Specialization of string -> string that simply returns
     * the string.
     */
    template <>
	OB_CORE_API std::string StringUtil::parse(const std::string& stringValue);

}

#include <oblivion/core/string_util_inl.h>

#endif /* _OBLIVION_CORE_STRING_UTIL_H_ */
