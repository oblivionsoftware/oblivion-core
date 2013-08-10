/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_STRING_UTIL_INL_H_
#define _OBLIVION_CORE_STRING_UTIL_INL_H_

namespace oblivion {

/*****************************************************************************/

template <typename T>
std::string toString(const T& value) {
    std::ostringstream ss;
    ss << value;

    return ss.str();
}

/*****************************************************************************/

template <typename K, typename V>
std::string toString(const std::pair<K,V>& value) {
    std::stringstream ss;
    ss << "(" << toString(value.first) << "," << toString(value.second) << ")";

    return ss.str();
}

/*****************************************************************************/

template <typename T>
std::string toString(const std::vector<T>& value) {
    return toCsv(value);
}

/*****************************************************************************/

template <typename T>
T fromString(const std::string& stringValue) {
    T result;
    std::istringstream ss(stringValue);
    ss >> result;

    return result;
}

/*****************************************************************************/

template <typename Iterator>
std::string toCsv(Iterator begin, Iterator end) {
    std::stringstream ss;

    int i = 0;
    for (auto itr = begin; itr != end; ++itr) {
        if (i > 0) {
            ss << ", ";
        }

        ss << toString(*itr);
        ++i;
    }

    return ss.str();
}

/*****************************************************************************/

template <typename Container>
std::string toCsv(const Container& container) {
    return toCsv(std::begin(container), std::end(container));
}

/*****************************************************************************/

}

#endif /* _OBLIVION_CORE_STRING_UTIL_INL_H_ */
