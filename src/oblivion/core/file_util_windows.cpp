/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file_util.h>

#include <oblivion/core/windows.h>

namespace oblivion {

/*****************************************************************************/

bool FileUtil::exists(const std::string& path) {
    DWORD attr = GetFileAttributes(path.c_str());
    return 0xFFFFFFFF != attr;
}

/**************************************************************************/

bool FileUtil::isDirectory(const std::string& path) {
    DWORD attr = GetFileAttributes(path.c_str());
    
    if (0xFFFFFFFF == attr) {
        return false;
    }

    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

/**************************************************************************/

void FileUtil::createDirectory(const std::string& path) {
    CreateDirectory(path.c_str(), nullptr);
}

/**************************************************************************/

std::vector<std::string> FileUtil::listFiles(const std::string& path) {
    std::vector<std::string> result;

    WIN32_FIND_DATA file;
    HANDLE fileList = FindFirstFile((path + "/*").c_str(), &file);

    if (fileList != INVALID_HANDLE_VALUE) {
        do {
            if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                result.push_back((path + "/") + file.cFileName);
            }
        } while (FindNextFile(fileList, &file));
    }

    FindClose(fileList);

    return result;
}

/*****************************************************************************/

}
