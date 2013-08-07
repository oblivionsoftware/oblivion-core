/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file.h>

#include <string>

#include <oblivion/core/exception.h>

namespace oblivion {

/*****************************************************************************/

File::File(const char* path, const char* mode) {
	file_ = fopen(path, mode);

	if (!file_) {
		OB_THROW(std::string("Unable to open file: ") + path);
	}
}

/*****************************************************************************/

File::~File() {
	close();
}

/*****************************************************************************/

void File::close() {
	if (file_) {
		fclose(file_);
		file_ = nullptr;
	}
}

/*****************************************************************************/

void File::seek(long int offset, int origin) {
	if (fseek(file_, offset, origin) != 0) {
        OB_THROW("fseek failed");
    }
}

/*****************************************************************************/

long int File::position() {
	auto result = ftell(file_);

	if (result == -1) {
		OB_THROW("ftell failed");
	}

	return result;
}

/*****************************************************************************/

size_t File::read(size_t size, void* out) {
	auto result = fread(out, 1, size, file_);

	if (result != size && !feof(file_)) {
		OB_THROW("fread failed");
	}

	return result;
}

/*****************************************************************************/

void File::write(size_t size, void* data) {
	if (fwrite(data, size, 1, file_) != 1) {
        OB_THROW("fwrite failed");
    }
}

/*****************************************************************************/

size_t File::size() {
	auto current = position();

	seek(0, SEEK_END);
	auto result = position();
	seek(current, SEEK_SET);

	return result;
}

/*****************************************************************************/

bool File::eof() {
	return feof(file_) != 0;
}

/*****************************************************************************/

void File::remove(const char* path) {
	if (std::remove(path) != 0) {
		OB_THROW(std::string("Unable to remove file: ") + path);
	}
}

/*****************************************************************************/

}
