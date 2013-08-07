/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/exception.h>

namespace oblivion {

/*****************************************************************************/

Exception::Exception(const std::string& what, const char* file, const char* function, int32 line) 
    : std::runtime_error(what),
      file_(file),
      function_(function),
      line_(line) {
}

/*****************************************************************************/

Exception::Exception(const char* what, const char* file, const char* function, int32 line) 
    : std::runtime_error(what),
      file_(file),
      function_(function),
      line_(line) {
}

/*****************************************************************************/

int32 Exception::line() const {
    return line_;
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

}
