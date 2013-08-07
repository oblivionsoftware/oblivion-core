/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_EXCEPTION_H_
#define _OBLIVION_CORE_EXCEPTION_H_

#include <stdexcept>
#include <string>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

/**
 * Macro for throwing an exception that injects the correct file, function, and line number.
 * @param message The message to throw.
 */
#define OB_THROW(message) throw oblivion::Exception((message), __FILE__, __FUNCTION__, __LINE__)

namespace oblivion {

    /**
     * Base class for all exceptions thrown by oblivion libraries.
     */
    class OB_CORE_API Exception : public std::runtime_error {

    public:

        /**
         * Constructs an exception with the specified error message.
         * @param what The error message.
         * @param file The name of the file.
         * @param function The name of the function throwing the error.
         * @param line The line number.
         */
        explicit Exception(const std::string& what, const char* file = nullptr, const char* function = nullptr, int32 line = -1);

        /**
         * Constructs an exception with the specified error message.
         * @param what The error message.
         * @param file The name of the file.
         * @param function The name of the function throwing the error.
         * @param line The line number.
         */
        explicit Exception(const char* what, const char* file = nullptr, const char* function = nullptr, int32 line = -1);

        /**
         * Gets the line number where the exception was thrown.
         * @return The line number.
         */
        int32 line() const;

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

    private:

        std::string file_;

        std::string function_;

        int32 line_;        

    };

}

#endif /* _OBLIVION_CORE_EXCEPTION_H_ */
