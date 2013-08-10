/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file.h>

#include <string>

#include <oblivion/core/exception.h>

namespace oblivion {

/*****************************************************************************/

File::File(const std::string& path, const char* mode) {
    file_ = fopen(path.c_str(), mode);

    if (!file_) {
        OB_THROW(std::string("Unable to open file: ") + path);
    }
}

/*****************************************************************************/

File::File(File&& other)
    : file_(other.file_) {

    other.file_ = nullptr;
}

/*****************************************************************************/

File::~File() {
    fclose(file_);
}

/*****************************************************************************/

File& File::operator =(File&& other) {
    fclose(file_);

    file_ = other.file_;
    other.file_ = nullptr;

    return *this;
}

/*****************************************************************************/

void File::flush() {
    fflush(file_);
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

void File::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(file_, format, args);
    va_end(args);
}

/*****************************************************************************/

void File::write(const std::string& text) {
    printf("%s", text.c_str());
}

/*****************************************************************************/

void File::writeLine(const std::string& line) {
    printf("%s\n", line.c_str());
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
