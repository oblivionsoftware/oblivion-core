
/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/properties.h>

#include <iostream>

#include <oblivion/core/exception.h>
#include <oblivion/core/file.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

Properties::Properties() {
}

/*****************************************************************************/

Properties::Properties(const std::string& path) {
    load(path);
}

/*****************************************************************************/

void Properties::setProperty(const std::string& name, const std::string& value) {
    properties_[name] = value;
}

/*****************************************************************************/

const std::string& Properties::getProperty(const std::string& name, const std::string& defaultValue) {
    if (contains(name)) {
        return properties_[name];
    }

    return defaultValue;
}

/*****************************************************************************/

bool Properties::contains(const std::string& name) {
    return properties_.find(name) != properties_.end();
}

/*****************************************************************************/

void Properties::save(const std::string& path) {
    File file(path, "wb");
    
    for (auto& entry : properties_) {
        file.writeLine(entry.first + " = " + entry.second);
    }
}

/*****************************************************************************/

void Properties::load(const std::string& path) {
    File file(path, "rb");

    while (!file.eof()) {
        auto line = file.readLine();
        trim(line);

        if (startsWith(line, "#") || line.empty()) {
            continue;
        }

        auto equalsPos = line.find_first_of("=");
        if (equalsPos == std::string::npos) {
            OB_THROW("Invalid property line: " + line);
        }

        auto name = line.substr(0, equalsPos);
        trim(name);

        auto value = line.substr(equalsPos + 1);
        trim(value);

        set(name, value);
    }
}

/*****************************************************************************/

Properties::const_iterator Properties::begin() const {
    return properties_.begin();
}

/*****************************************************************************/

Properties::const_iterator Properties::end() const {
    return properties_.end();
}

/*****************************************************************************/

int32 Properties::size() const {
    return static_cast<int32>(properties_.size());
}

/*****************************************************************************/

bool Properties::empty() const {
    return properties_.empty();
}

/*****************************************************************************/

void Properties::clear() {
    properties_.clear();
}

/*****************************************************************************/

}
