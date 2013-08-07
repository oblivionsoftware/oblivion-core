/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file.h>

#include <oblivion/core/windows.h>

namespace oblivion {

/*****************************************************************************/

bool File::exists(const char* path) {
	DWORD attr = GetFileAttributes(path);
	return 0xFFFFFFFF != attr;
}

/*****************************************************************************/

}
