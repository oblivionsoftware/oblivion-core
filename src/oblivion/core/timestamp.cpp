/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/timestamp.h>

#include <iostream>

namespace oblivion {

/*****************************************************************************/

/**
 * The ISO 8601 Format string.
 */
static const std::string ISO_8601_FORMAT = "%Y-%m-%dT%H:%M:%SZ";

/**
 * The default DateTime format.
 */
static const std::string DEFAULT_DATE_TIME_FORMAT = "%x %X";

/*****************************************************************************/

Timestamp::Timestamp() {
    time_ = std::time(nullptr);
}

/*****************************************************************************/

std::string Timestamp::iso8601() const {
    char buffer[128];
    strftime(buffer, 128, ISO_8601_FORMAT.c_str(), std::gmtime(&time_));

    return buffer;
}

/*****************************************************************************/

std::string Timestamp::format(const std::string& format) const {
    char buffer[128];
    strftime(buffer, 128, format.c_str(), std::localtime(&time_));

    return buffer;
}

/*****************************************************************************/

void Timestamp::print(std::ostream& os) const {
    os << format(DEFAULT_DATE_TIME_FORMAT);
}

/*****************************************************************************/

std::ostream& operator <<(std::ostream& os, const Timestamp& timestamp) {
    timestamp.print(os);
    return os;
}

/*****************************************************************************/

}
