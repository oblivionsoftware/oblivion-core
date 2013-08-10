/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_FILE_H_
#define _OBLIVION_CORE_FILE_H_

#include <cstdio>
#include <string>

#include <oblivion/core/base.h>
#include <oblivion/core/non_copyable.h>

namespace oblivion {

    /**
     * RAII wrapper around stdio FILE.
     */
    class OB_CORE_API File : NonCopyable {

    public:

        /** 
         * Opens the specified file.
         * @param path The path to the file to open.
         * @param mode The mode string (@see fopen).
         * @throw Exception if the file cannot be opened.
         */
        File(const std::string& path, const char* mode);

        /**
         * Moves constructs a file.
         * @param other The file to move.
         */
        File(File&& other);

        /**
         * Closes the file if opened.
         */
        ~File();

        /**
         * Move assignment.
         * @param other The file to move.
         * @return A reference to this file.
         */
        File& operator =(File&& other);

        /** 
         * Flushes the file stream to the filesystem.
         */
        void flush();

        /**
         * Seeks to a position in the file. (@see fseek).
         * @param offset The number of bytes to offset from origin.
         * @param origin Position used as a reference for the offset. Possible values are (SEEK_SET, SEEK_CUR or SEEK_END).
         * @throw Excception if the operation fails.
         */
        void seek(long int offset, int origin);

        /**
         * Gets the current position of the file.
         * @return The current file position.
         * @throw Exception if the operation fails.
         */
        long int position();

        /**
         * Reads data from a file.
         * @param size The number of bytes to read.
         * @param out The output parameter for the file data.
         * @return The number of bytes read.
         * @throw Exception if the read operation fails.
         */
        size_t read(size_t size, void* out);

        /**
         * Writes data to a file.
         * @param size The size of the data to write.
         * @param data The data to write. 
         * @throw Exception if the write operation fails.
         */
        void write(size_t size, void* data);

        /**
         * Writes formatted output to a file.
         * @param format The printf style format string.
         */
        void printf(const char* format, ...);

        /**
         * Writes some text to the file.
         * @param text The text to write.
         */
        void write(const std::string& text);

        /**
         * Writes a line of text to the file.
         * @param line The line to write.
         */
        void writeLine(const std::string& line);

        /**
         * Gets the size of the specified file.
         * @param out The output parameter for the file size.
         * @return The file size.
         * @throw Exception if the operation fails.
         */
        size_t size();
        /**
         * Gets whether or not the file is currently at the end of input.
         * @return True if the file is at the end of input, false otherwise.
         */
        bool eof();

        /**
         * Gets whether or not the specified file exists.
         * @param path The path to the file to check.
         */
        static bool exists(const char* path);

        /**
         * Removes the file at the specified location.
         * @param path The path to the file to delete.
         * @throw Exception If the file is not able to be deleted.
         */
        static void remove(const char* path);

    private:

        FILE* file_;

    };

}

#endif /* _OBLIVION_CORE_FILE_H_ */
