/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/file.h>

#include <cstdarg>
#include <string>

#include <oblivion/core/exception.h>

namespace oblivion {

/*****************************************************************************/

const int32 MAX_LINE_SIZE = 2048;

/*****************************************************************************/

File::File(const std::string& path, const char* mode) {
    file_ = fopen(path.c_str(), mode);

    if (!file_) {
        OB_THROW("Unable to open file: %s", path.c_str());
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

std::string File::readLine() {
    char buffer[MAX_LINE_SIZE];
    if (!fgets(buffer, sizeof(buffer), file_)) {
        if (feof(file_)) {
            return "";
        }

        OB_THROW("fgets failed");
    }

    return buffer;
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

}
