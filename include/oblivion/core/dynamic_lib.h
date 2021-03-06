/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_DYNAMIC_LIB_H_
#define _OBLIVION_CORE_DYNAMIC_LIB_H_

#include <memory>
#include <string>

#include <oblivion/core/base.h>
#include <oblivion/core/non_copyable.h>

namespace oblivion {

    /**
     * Loads/Unloads shared libraries dynamically and provides access to symbols.
     */
    class OB_CORE_API DynamicLib : NonCopyable {

    public:

        /**
         * Opens the specified dynamic library.
         * @param path The path to the library to open.
         * @throw Exception if the library cannot be opened.
         */
        explicit DynamicLib(const std::string& path);

        /**
         * Closes the dynamic library.
         */
        ~DynamicLib();

        /**
         * Gets a pointer to the function with the specified name.
         * @param name The name of the function.
         * @return A pointer to the function.
         * @throw Exception if the function cannot be found.
         */
        void* getFunction(const std::string& name);

        /**
         * Gets the path that this library was loaded from.
         * @return The path.
         */
        const std::string& path() const;

    private:

        struct Impl;
        std::unique_ptr<Impl> impl_;

    };

}

#endif /* _OBLIVION_CORE_DYNAMIC_LIB_H_ */
