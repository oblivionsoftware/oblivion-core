/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file_util.h>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace oblivion {

/*****************************************************************************/

bool FileUtil::exists(const std::string& path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}

/**************************************************************************/

bool FileUtil::isDirectory(const std::string& path) {
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0) {
        return ((fileStat.st_mode & S_IFDIR) != 0);
    }

    return false;
}

/**************************************************************************/

void FileUtil::createDirectory(const std::string& path) {
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

/**************************************************************************/

std::vector<std::string> FileUtil::listFiles(const std::string& path) {
     std::vector<std::string> result;
        
    auto dir = opendir(path.c_str());
    
    if (dir) {
        struct dirent* dirEntry;
    
        while ((dirEntry = readdir(dir)) != nullptr) {
            std::string fileName(dirEntry->d_name);
            
            if (fileName == "."  || fileName == "..") {
                continue;
            }
        
            result.push_back((path + "/") + fileName);
        }
    
        closedir(dir);
    }    
    
    return result;
}

/**************************************************************************/

}
