/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/exception.h>

#include <cstdarg>
#include <sstream>

#include <oblivion/core/string_util.h>

namespace oblivion {

/*****************************************************************************/

Exception::Exception(const char* file, const char* function, int32 line, const std::string& message) 
    : message_(message),
      file_(file),
      function_(function),
      line_(line) {

    std::stringstream ss;
    ss << message_ << " - " << function_ << " - " << file_ << "(" << line_ << ")";

    fullMessage_ = ss.str();
}

/*****************************************************************************/

Exception::Exception(const char* file, const char* function, int32 line, const char* format, ...) 
    : file_(file),
      function_(function),
      line_(line) {

    va_list args;
    va_start(args, format);
    message_ = formatString(format, args);
    va_end(args);

    std::stringstream ss;
    ss << message_ << " - " << function_ << " - " << file_ << "(" << line_ << ")";

    fullMessage_ = ss.str(); 
}

/*****************************************************************************/

int32 Exception::line() const {
    return line_;
}

/*****************************************************************************/

const std::string& Exception::message() const {
    return message_;
}

/*****************************************************************************/

const std::string& Exception::file() const {
    return file_;
}

/*****************************************************************************/

const std::string& Exception::function() const {
    return function_;
}

/*****************************************************************************/

const char* Exception::what() const throw() {
    return fullMessage_.c_str();
}

/*****************************************************************************/

}
