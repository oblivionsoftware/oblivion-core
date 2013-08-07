/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_FILE_H_
#define _OBLIVION_CORE_FILE_H_

#include <cstdio>

#include <oblivion/core/base.h>

namespace oblivion {

	/**
	 * RAII wrapper around stdio FILE.
	 */
	class OB_CORE_API File {

	public:

		/** 
		 * Opens the specified file.
		 * @param path The path to the file to open.
		 * @param mode The mode string (@see fopen).
		 * @throw Exception if the file cannot be opened.
		 */
		File(const char* path, const char* mode);

		/**
		 * Closes the file if opened.
		 */
		~File();

		/**
		 * Closes the file.
		 */
		void close();

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
