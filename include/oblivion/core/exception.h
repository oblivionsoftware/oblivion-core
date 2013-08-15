/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_EXCEPTION_H_
#define _OBLIVION_CORE_EXCEPTION_H_

#include <exception>
#include <string>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

/**
 * Macro for throwing an exception that injects the correct file, function, and line number.
 * @param message The message to throw.
 */
#define OB_THROW(...) throw oblivion::Exception(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

/**
 * Throws a "Not Implemented" exception.
 */
#define OB_NOT_IMPLEMENTED OB_THROW("Not Implemented");

namespace oblivion {

    /**
     * Base class for all exceptions thrown by oblivion libraries.
     */
    class OB_CORE_API Exception : public std::exception {

    public:

        /**
         * Constructs an exception with the specified error message.
         * @param file The name of the file.
         * @param function The name of the function throwing the error.
         * @param line The line number.
         * @param message The error message.
         */
        Exception(const char* file, const char* function, int32 line, const std::string& message);

        /**
         * Constructs an exception with the specified error message.
         * @param file The name of the file.
         * @param function The name of the function throwing the error.
         * @param line The line number.
         * @param format The printf style format string.
         */
        Exception(const char* file, const char* function, int32 line, const char* format, ...);

        /**
         * Gets the line number where the exception was thrown.
         * @return The line number.
         */
        int32 line() const;

        /**
         * Gets the exception message.
         * @return The exception message.
         */
        const std::string& message() const;

        /**
         * Gets the name of the file from which the exception was thrown.
         * @return The name of the file.
         */
        const std::string& file() const;

        /**
         * Gets the name of the function from which the exception was thrown.
         * @return The name of the function.
         */
        const std::string& function() const;

        /**
         * Gets the full exception message.
         * @return The full message.
         */
        virtual const char* what() const throw();

    private:

        std::string message_;

        std::string file_;

        std::string function_;

        int32 line_;        

        std::string fullMessage_;

    };

}

#endif /* _OBLIVION_CORE_EXCEPTION_H_ */
