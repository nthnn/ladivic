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

#include <atomic>
#include <iostream>
#include <mutex>

#include <ldvc_atomic.hpp>
#include <ldvc_io.hpp>

/**
 * 
 * @brief Main function to demonstrate atomic operations and file I/O.
 *
 * This function demonstrates the usage of atomic operations and file I/O operations
 * provided by the LDVC library.
 *
 * @return 0 on success, 1 on failure.
 * 
 */
int main() {
    try {
        // Create a mutex and an atomic real value
        std::mutex mtx;
        std::atomic<real> real_value;

        // Create an atomic real value with initial value 3.14
        ldvc_atomic_create(real_value, mtx, 3.14);

        // Write the atomic real value to a file
        ldvc_write_file("real_data.dat", real_value);

        // Read the real value from the file
        real read_value = ldvc_read_file<real>("real_data.dat");
        std::cout << "Read real value: " << read_value << std::endl;

        // Define a folder path for testing file existence and creation
        string folder_path = "example_folder";

        // Check if the folder exists
        if(!ldvc_file_exists(folder_path)) {
            // If the folder doesn't exist, attempt to create it
            if(ldvc_create_folder(folder_path, 0777))
                std::cout << "Folder created successfully: " << folder_path << std::endl;
            else std::cerr << "Failed to create folder: " << folder_path << std::endl;
        }
        else {
            // If the folder already exists, inform the user
            std::cout << "Folder already exists: " << folder_path << std::endl;
        }
    }
    catch(const std::exception& e) {
        // Handle exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}