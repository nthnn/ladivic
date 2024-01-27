/*
 * This file is part of the ladivic library.
 * Copyright (c) 2024 Nathanne Isip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * 
 * @file ldvc_io.hpp
 * @brief Provides utilities for file input/output operations in C++.
 *
 * This header file defines functions for performing file input/output operations in C++,
 * including writing data to a file, reading data from a file, checking file existence,
 * and creating folders.
 *
 * @author Nathanne Isip
 * 
 */

#ifndef LDVC_IO_HPP
#define LDVC_IO_HPP

#include <fstream>
#include <string>
#include <stdexcept>
#include <sys/stat.h>
#include <ldvc_type.hpp>

/**
 * 
 * @brief Writes data to a file.
 *
 * This function writes the specified data to a file with the
 * given filename. It opens the file in binary mode for writing
 * and writes the binary representation of the data to the file.
 *
 * @tparam T The type of data to be written to the file.
 * 
 * @param filename The filename of the file to write to.
 * @param data The data to be written to the file.
 * 
 * @throw std::runtime_error Thrown if the file cannot be opened for writing.
 * 
 */
template <typename T>
void ldvc_write_file(const string& filename, const T& data)
{
    std::ofstream out_file(filename, std::ios::binary);
    if(!out_file.is_open())
        throw std::runtime_error("Failed to open file for writing: " + filename);

    out_file.write(reinterpret_cast<const rune*>(&data), sizeof(T));
    out_file.close();
}

/**
 * 
 * @brief Reads data from a file.
 *
 * This function reads data from a file with the given filename and returns it.
 * It opens the file in binary mode for reading and reads the binary representation
 * of the data from the file.
 *
 * @tparam T The type of data to be read from the file.
 * 
 * @param filename The filename of the file to read from.
 * 
 * @return T The data read from the file.
 * 
 * @throw std::runtime_error Thrown if the file cannot be opened for reading.
 * 
 */
template <typename T>
T ldvc_read_file(const string& filename)
{
    std::ifstream in_file(filename, std::ios::binary);
    if(!in_file.is_open())
        throw std::runtime_error("Failed to open file for reading: " + filename);

    T data;
    in_file.read(reinterpret_cast<rune*>(&data), sizeof(T));
    in_file.close();

    return data;
}

/**
 * 
 * @brief Checks if a file exists.
 *
 * This function checks if a file exists at the specified path.
 *
 * @param filename The filename or path of the file to check.
 * 
 * @return bool True if the file exists, false otherwise.
 * 
 */
bool ldvc_file_exists(const string& folder_path);

/**
 * 
 * @brief Creates a folder with the specified permissions.
 *
 * This function creates a folder at the specified path with the given permissions.
 *
 * @param folder_path The path of the folder to create.
 * @param mode The permissions for the folder.
 * 
 * @return bool True if the folder was created successfully, false otherwise.
 * 
 */
bool ldvc_create_folder(const string& folder_path, u16 mode);

#endif