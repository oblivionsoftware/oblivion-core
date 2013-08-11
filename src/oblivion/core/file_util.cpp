/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file_util.h>

#include <oblivion/core/exception.h>
#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

void FileUtil::remove(const std::string& path) {
    if (std::remove(path.c_str()) != 0) {
        OB_THROW("Unable to remove file: " + path);
    }
}

/*****************************************************************************/

std::string FileUtil::getExtension(const std::string& path) {
    auto fileName = getFileName(path);

    auto firstDot = fileName.find_first_of(".");

    if (firstDot == std::string::npos) {
        return "";
    }    

    return fileName.substr(firstDot);
}

/*****************************************************************************/

std::string FileUtil::getBaseName(const std::string& path) {
    auto fileName = getFileName(path);

    auto firstDot = fileName.find_first_of(".");
    return fileName.substr(0, firstDot);
}

/*****************************************************************************/

std::string FileUtil::getFileName(const std::string& path) {
    auto cleanPath = path;
    while (endsWith(cleanPath, "\\") || endsWith(cleanPath, "/")) {
        cleanPath = cleanPath.substr(0, cleanPath.size() - 1);
    }

    auto lastSlash = cleanPath.find_last_of("\\/");

    if (lastSlash == std::string::npos) {
        return cleanPath;
    }

    return cleanPath.substr(lastSlash + 1);
}

/*****************************************************************************/

}
