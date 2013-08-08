/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/exception.h>

#include <sstream>

namespace oblivion {

/*****************************************************************************/

Exception::Exception(const std::string& message, const char* file, const char* function, int32 line) 
    : message_(message),
      file_(file),
      function_(function),
      line_(line) {

    std::stringstream ss;
    ss << message_ << " - " << function_ << " - " << file_ << "(" << line_ << ")";

    fullMessage_ = ss.str();
}

/*****************************************************************************/

int32 Exception::line() const {
     int a;
     int b = 3 + a;
     std::string bad = "asdf" + 'c';

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
