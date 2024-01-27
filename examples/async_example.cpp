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

#include <iostream>
#include <thread>
#include <mutex>
#include <stdexcept>

#include <ldvc_async.hpp>
#include <ldvc_atomic.hpp>
#include <ldvc_type.hpp>

/**
 * 
 * @brief Thread-safe function to increment an atomic integer.
 *
 * This function increments the value of an atomic integer using
 * the provided mutex for thread safety.
 *
 * @param mtx The mutex used to ensure thread safety.
 * @param value The atomic integer to increment.
 * 
 * @return The incremented value.
 * 
 */
i32 thread_safe_increment(std::mutex& mtx, std::atomic<i32>& value) {
    ldvc_atomic_inc(value, mtx, 1);
    return ldvc_atomic_load(value, mtx);
}

/**
 * 
 * @brief Thread-safe function to decrement an atomic integer.
 *
 * This function decrements the value of an atomic integer using
 * the provided mutex for thread safety.
 *
 * @param mtx The mutex used to ensure thread safety.
 * @param value The atomic integer to decrement.
 * 
 * @return The decremented value.
 * 
 */
i32 thread_safe_decrement(std::mutex& mtx, std::atomic<i32>& value) {
    ldvc_atomic_dec(value, mtx, 1);
    return ldvc_atomic_load(value, mtx);
}

/**
 * 
 * @brief Main function to demonstrate thread-safe operations.
 *
 * This function demonstrates the usage of thread-safe operations such as atomic
 * increments and decrements, asynchronous function execution with delay and timeout.
 *
 * @return 0 on success, 1 on failure.
 * 
 */
i32 main() {
    std::mutex mtx;
    std::atomic<i32> value;

    ldvc_atomic_create(value, mtx, 0);
    try {
        // Execute thread-safe increment and decrement operations asynchronously
        std::future<i32> future_inc = ldvc_async_execute(thread_safe_increment, std::ref(mtx), std::ref(value));
        std::future<i32> future_dec = ldvc_async_execute(thread_safe_decrement, std::ref(mtx), std::ref(value));

        // Execute a function with a delay of 1 second asynchronously
        std::future<void> future_delay = ldvc_async_execute_with_delay(std::chrono::seconds(1), []() {
            std::cout << "Delayed function executed" << std::endl;
        });

        // Execute a function with a timeout of 2 seconds asynchronously
        std::future<void> future_timeout = ldvc_async_execute_with_timeout(std::chrono::seconds(2), []() {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "This function should not be reached due to timeout" << std::endl;
        });

        // Wait for all futures to complete
        future_inc.wait();
        future_dec.wait();
        future_delay.wait();
        future_timeout.wait();

        // Retrieve results from futures
        i32 result_inc = future_inc.get();
        i32 result_dec = future_dec.get();

        // Output results
        std::cout << "Incremented value: " << result_inc << std::endl;
        std::cout << "Decremented value: " << result_dec << std::endl;
    }
    catch (const std::exception& e) {
        // Handle exceptions
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
