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
 * @file ldvc_mem.hpp
 * @brief Memory management utilities for dynamic allocation and deallocation.
 *
 * This header file provides functions for dynamic memory allocation and deallocation,
 * including allocation, reallocation, and deallocation of memory blocks. Thread safety
 * is ensured during these operations using a mutex.
 * 
 * @author Nathanne Isip
 * 
 */
#ifndef LDVC_MEM_HPP
#define LDVC_MEM_HPP

#include <cstddef>
#include <mutex>
#include <ldvc_type.hpp>

/// Mutex for thread-safe memory management
std::mutex ldvc_mem_mutx;

/**
 * 
 * @brief Allocates memory for an array of elements.
 *
 * This function allocates memory for an array of elements
 * of type T with the specified size.
 *
 * @tparam T The type of elements to allocate memory for.
 * 
 * @param size The number of elements to allocate memory for.
 * 
 * @return A pointer to the allocated memory block, or nullptr if allocation fails.
 * 
 */
template <typename T>
T* ldvc_malloc(usize size)
{
    const std::lock_guard<std::mutex> lock(ldvc_mem_mutx);

    T* ptr = static_cast<T*>(::operator new(size * sizeof(T)));
    if(ptr == nullptr)
        return (int*) -1;

    return ptr;
}

/**
 * 
 * @brief Deallocates memory previously allocated by ldvc_malloc or similar functions.
 *
 * This function deallocates memory previously allocated by ldvc_malloc or similar functions.
 *
 * @tparam T The type of elements in the memory block to deallocate.
 * 
 * @param object A pointer to the memory block to deallocate.
 * 
 */
template <typename T>
void ldvc_free(T* object)
{
    const std::lock_guard<std::mutex> lock(ldvc_mem_mutx);
    ::operator delete(object);
}

/**
 * 
 * @brief Reallocates memory for an array of elements.
 *
 * This function reallocates memory for an array of elements of
 * type T with the specified size.
 *
 * @tparam T The type of elements to reallocate memory for.
 * 
 * @param ptr A pointer to the memory block to reallocate.
 * @param size The new number of elements to allocate memory for.
 * 
 * @return A pointer to the reallocated memory block, or nullptr if reallocation fails.
 * 
 */
template <typename T>
T* ldvc_realloc(T* ptr, usize size)
{
    T* new_ptr = ldvc_malloc<T>(size);
    if(ptr != nullptr) {
        for (size_t i = 0; i < size; ++i)
            new_ptr[i] = ptr[i];
        ldvc_free(ptr);
    }

    return new_ptr;
}

/**
 * 
 * @brief Allocates and initializes memory for an array of elements.
 *
 * This function allocates memory for an array of elements of type
 * T with the specified size and initializes all elements to zero.
 *
 * @tparam T The type of elements to allocate memory for.
 * 
 * @param num The number of elements to allocate memory for.
 * 
 * @return A pointer to the allocated memory block, or nullptr if allocation fails.
 * 
 */
template <typename T>
T* ldvc_calloc(usize num)
{
    T* ptr = ldvc_malloc<T>(num);

    if(ptr != nullptr)
        for (size_t i = 0; i < num; ++i)
            ptr[i] = T();
    return ptr;
}

#endif