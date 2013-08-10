/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_PROPERTIES_INL_H_
#define _OBLIVION_CORE_PROPERTIES_INL_H_

#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

template <typename T>
void Properties::set(const std::string& name, const T& value) {
    setProperty(name, toString(value));
}

/*****************************************************************************/

template <typename T>
T Properties::get(const std::string& name, const T& defaultValue) const {
    if (contains(name)) {
        return fromString<T>(getProperty(name));
    }

    return defaultValue;
}

/*****************************************************************************/

}

#endif /* _OBLIVION_CORE_PROPERTIES_INL_H_ */
