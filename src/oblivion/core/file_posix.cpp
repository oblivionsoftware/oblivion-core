/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file.h>

#include <sys/stat.h>

namespace oblivion {

/*****************************************************************************/

bool File::exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

/*****************************************************************************/

}
