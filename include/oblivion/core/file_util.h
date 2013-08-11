/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_FILE_UTIL_H_
#define _OBLIVION_CORE_FILE_UTIL_H_

#include <string>
#include <vector>

#include <oblivion/core/base.h>

namespace oblivion {

    /**
     * File utility functions.
     */
    class OB_CORE_API FileUtil {

    public:

        /**
         * Gets whether or not the specified file exists.
         * @param path The path to the file to check.
         */
        static bool exists(const std::string& path);

        /**
         * Removes the file at the specified location.
         * @param path The path to the file to delete.
         * @throw Exception If the file is not able to be deleted.
         */
        static void remove(const std::string& path);

        /**
         * Gets whether or not the specified path is a directory.
         * @param path The path to check.
         * @return True if the path exists and is a directory, false otherwise.
         */
        static bool isDirectory(const std::string& path);

        /**
         * Creates the specified directory if it does not already exist.
         * @param path The directory to create.
         */
        static void createDirectory(const std::string& path);

        /**
         * Gets the file extension (including the .) for the specified file path.
         * @param path The path to the file.
         * @return The file extension (including the .).
         */
        static std::string getExtension(const std::string& path);

        /**
         * Gets the base filename for the specified file path.
         * @param path The path to the file.
         * @return The base filename (without the extension)
         */
        static std::string getBaseName(const std::string& path);

        /**
         * Gets the filename for the specified path.
         * @param path The file name.
         * @return The filename.
         */
        static std::string getFileName(const std::string& path);

        /**
         * Lists the files in a directory.
         * @param path The path to the directory to iterate.
         * @return The list of paths to files in the directory.
         */
        static std::vector<std::string> listFiles(const std::string& path);

    };

}

#endif /* _OBLIVION_CORE_FILE_UTIL_H_ */
