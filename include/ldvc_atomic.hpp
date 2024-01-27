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
 * @file ldvc_atomic.hpp
 * @brief Provides utilities for atomic operations with mutex protection in C++.
 *
 * This header file defines functions for performing atomic operations on `std::atomic` variables
 * with the protection of a mutex. These functions ensure thread safety while allowing atomicity
 * for operations such as incrementing, decrementing, bitwise operations, exchange, load, and store.
 *
 * @author Nathanne Isip
 * 
 */
#ifndef LDVC_ATOMIC_HPP
#define LDVC_ATOMIC_HPP

#include <atomic>
#include <mutex>

/**
 * 
 * @brief Initializes an `std::atomic` variable with the specified
 *        initial value under the protection of a mutex.
 *
 * This function initializes an `std::atomic` variable `var` with
 * the specified initial value `value` under the protection of the
 * provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be initialized.
 * @param mutex The mutex for thread safety.
 * @param value The initial value for the atomic variable.
 * 
 */
template <typename T>
void ldvc_atomic_create(std::atomic<T>& var, std::mutex& mutex, T value)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.store(value, std::memory_order_relaxed);
}

/**
 * 
 * @brief Resets an `std::atomic` variable to its
 *        default-constructed value under the protection
 *        of a mutex.
 *
 * This function resets an `std::atomic` variable `var`
 * to its default-constructed value under the protection of
 * the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * @param var The atomic variable to be reset.
 * @param mutex The mutex for thread safety.
 */
template<typename T>
void ldvc_atomic_delete(std::atomic<T>& var, std::mutex& mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.store(T{}, std::memory_order_relaxed);
}

/**
 * 
 * @brief Atomically increments the value of an `std::atomic`
 *        variable by the specified amount under the protection of a mutex.
 *
 * This function atomically increments the value of an `std::atomic`
 * variable `var` by the specified amount `arg` under the protection
 * of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be incremented.
 * @param mutex The mutex for thread safety.
 * @param arg The amount by which to increment the atomic variable.
 * 
 */
template <typename T>
void ldvc_atomic_inc(std::atomic<T>& var, std::mutex& mutex, T arg)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.fetch_add(arg, std::memory_order_relaxed);
}

/**
 * 
 * @brief Atomically decrements the value of an `std::atomic`
 *        variable by the specified amount under the protection
 *        of a mutex.
 *
 * This function atomically decrements the value of an `std::atomic`
 * variable `var` by the specified amount `arg` under the protection
 * of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be decremented.
 * @param mutex The mutex for thread safety.
 * @param arg The amount by which to decrement the atomic variable.
 * 
 */
template <typename T>
void ldvc_atomic_dec(std::atomic<T>& var, std::mutex& mutex, T arg)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.fetch_sub(arg, std::memory_order_relaxed);
}

/**
 * 
 * @brief Performs a bitwise AND operation on an `std::atomic`
 *        variable with the specified value under the protection
 *        of a mutex.
 *
 * This function performs a bitwise AND operation on an `std::atomic`
 * variable `var` with the specified value `arg` under the protection
 * of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be bitwise ANDed.
 * @param mutex The mutex for thread safety.
 * @param arg The value for the bitwise AND operation.
 * 
 */
template <typename T>
void ldvc_atomic_and(std::atomic<T>& var, std::mutex& mutex, T arg)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.fetch_and(arg, std::memory_order_relaxed);
}

/**
 * 
 * @brief Performs a bitwise OR operation on an `std::atomic`
 * variable with the specified value under the protection of a mutex.
 *
 * This function performs a bitwise OR operation on an `std::atomic`
 * variable `var` with the specified value `arg` under the protection
 * of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be bitwise ORed.
 * @param mutex The mutex for thread safety.
 * @param arg The value for the bitwise OR operation.
 * 
 */
template <typename T>
void ldvc_atomic_or(std::atomic<T>& var, std::mutex& mutex, T arg)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.fetch_or(arg, std::memory_order_relaxed);
}

/**
 * 
 * @brief Performs a bitwise XOR operation on an `std::atomic`
 *        variable with the specified value under the protection
 *        of a mutex.
 *
 * This function performs a bitwise XOR operation on an `std::atomic`
 * variable `var` with the specified value `arg` under the protection
 * of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be bitwise XORed.
 * @param mutex The mutex for thread safety.
 * @param arg The value for the bitwise XOR operation.
 * 
 */
template <typename T>
void ldvc_atomic_xor(std::atomic<T>& var, std::mutex& mutex, T arg)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.fetch_xor(arg, std::memory_order_relaxed);
}

/**
 * @brief Atomically exchanges the value of an `std::atomic` variable
 *        with a new value under the protection of a mutex.
 *
 * This function atomically exchanges the value of an `std::atomic`
 * variable `var` with the specified new value `new_value`
 * under the protection of the provided mutex `mutex`. It returns the
 * previous value of the atomic variable.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be exchanged.
 * @param mutex The mutex for thread safety.
 * @param new_value The new value to be stored in the atomic variable.
 * 
 * @return T The previous value of the atomic variable.
 * 
 */
template <typename T>
T ldvc_atomic_exchange(std::atomic<T>& var, std::mutex& mutex, T new_value)
{
    std::lock_guard<std::mutex> lock(mutex);
    return var.exchange(new_value, std::memory_order_relaxed);
}

/**
 * @brief Atomically loads the value of an `std::atomic` variable
 *        under the protection of a mutex.
 *
 * This function atomically loads the value of an `std::atomic`
 * variable `var` under the protection of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be loaded.
 * @param mutex The mutex for thread safety.
 * 
 * @return T The value of the atomic variable.
 * 
 */
template <typename T>
T ldvc_atomic_load(const std::atomic<T>& var, std::mutex& mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    return var.load(std::memory_order_relaxed);
}

/**
 * 
 * @brief Atomically stores a new value in an `std::atomic`
 *        variable under the protection of a mutex.
 *
 * This function atomically stores the specified new value
 * `new_value` in an `std::atomic` variable `var`
 * under the protection of the provided mutex `mutex`.
 *
 * @tparam T The type of the atomic variable.
 * 
 * @param var The atomic variable to be stored.
 * @param mutex The mutex for thread safety.
 * @param new_value The new value to be stored in the atomic variable.
 * 
 */
template <typename T>
void ldvc_atomic_store(std::atomic<T>& var, std::mutex& mutex, T new_value)
{
    std::lock_guard<std::mutex> lock(mutex);
    var.store(new_value, std::memory_order_relaxed);
}

#endif