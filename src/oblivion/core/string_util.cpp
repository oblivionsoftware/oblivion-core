/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/string_util.h>

#include <algorithm>
#include <cctype>
#include <cstdio>

namespace oblivion {

/*****************************************************************************/

std::string StringUtil::escapeQuotes(const std::string& text) {
    std::ostringstream ss;

    for (auto c : text) {
        if (c == '"') {
            ss << "\\\"";
        } else if (c == '\'') {
            ss << "\\'";
        } else {
            ss << c;
        }
    }

    return ss.str();
}

/******************************************************************************/

void StringUtil::trim(std::string& text) {
    if (text.empty()) {
        return;
    }

    auto first = text.find_first_not_of(" \t\r\n");
    auto last = text.find_last_not_of(" \t\r\n");

    if (first == 0 && last == (text.size() - 1)) {
        return;
    }

    if (first == std::string::npos) {
        text.clear();
    } else {
        text = text.substr(first, (last - first) + 1);
    }
}

/******************************************************************************/

static char asciiHexToDecimal(char c) {
    switch (std::toupper(c)) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A': return 10;
    case 'B': return 11;
    case 'C': return 12;
    case 'D': return 13;
    case 'E': return 14;
    case 'F': return 15;
    default:  return 0;
    }
}

/******************************************************************************/

static char percentDecode(char a, char b) {
    return (asciiHexToDecimal(a) * 16) + asciiHexToDecimal(b);
}

/******************************************************************************/

std::string StringUtil::urlDecode(const std::string& input) {
    std::string result;

    for (auto i = 0u; i < input.length(); ++i) {
        auto c = input[i];

        switch (c) {
        case '%':
            if ((i + 2) < input.length()) {
                auto a = input[++i];
                auto b = input[++i];

                result += percentDecode(a, b);
            }
            break;
        case '+':
            result += ' ';
            break;
        default:
            result += c;
            break;
        }
    }

    return result;
}

/******************************************************************************/

std::string StringUtil::toUpper(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    return input;
}

/******************************************************************************/

std::string StringUtil::toLower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

/******************************************************************************/

std::string StringUtil::camelCaseToUnderscores(const std::string& input) {
    std::stringstream ss;

    for (auto i = 0u; i < input.length(); ++i) {
        char c = input[i];

        if (std::isupper(c)) {
            char lowerC = static_cast<char>(::tolower(c));

            if ((i + 1) < input.length() && !std::isupper(input[i + 1]) && input[i + 1] != '_' && (i == 0 || input[i - 1] != '_')) {
                ss << "_";
            } 

            ss << lowerC;
        } else {
            ss << c;
        }
    }

    return ss.str();
}

/******************************************************************************/

bool StringUtil::contains(const std::string& input, const std::string& search) {
    return input.find(search) != std::string::npos;
}

/******************************************************************************/

bool StringUtil::startsWith(const std::string& input, const std::string& search) {
    return input.find(search) == 0;
}

/******************************************************************************/

bool StringUtil::endsWith(const std::string& input, const std::string& search) {
    auto pos = input.rfind(search);

    if (pos == std::string::npos) {
        return false;
    }

    return pos == (input.size() - search.size());
}

/******************************************************************************/

std::string StringUtil::formatString(const char* format, ...) {
    va_list args;
    va_start(args, format);

    auto result = formatString(format, args);
    va_end(args);

    return result;
}

/******************************************************************************/

std::string StringUtil::formatString(const char* format, va_list args) {
    char buffer[2048];
    vsprintf(buffer, format, args);

    return buffer;
}

/*****************************************************************************/

std::vector<std::string> StringUtil::split(const std::string& text, char delimiter, bool trimTokens) {
    std::vector<std::string> result;

    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        if (trimTokens) {
            trim(item);
        }

        result.push_back(item);
    }

    return result;
}

/******************************************************************************/

template <>
std::string StringUtil::toString(const bool& value) {
    return value ? "true" : "false";
}

/******************************************************************************/

template <>
bool StringUtil::parse(const std::string& stringValue) {
    return StringUtil::toLower(stringValue) == "true";
}

/******************************************************************************/

template <>
std::string StringUtil::parse(const std::string& stringValue) {
    return stringValue;
}

/*****************************************************************************/

}
