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
#include <ldvc_atomic.hpp>
#include <ldvc_type.hpp>

/**
 * 
 * @brief Demonstrates various atomic operations on an atomic integer.
 *
 * This function demonstrates various atomic operations such as increment, decrement,
 * bitwise AND, bitwise OR, bitwise XOR, exchange, load, and store on an atomic integer.
 *
 * @return 0 on success.
 * 
 */
i32 main() {
    std::mutex mtx;
    std::atomic<i32> atom_i32;

    // Create an atomic integer with initial value 0
    ldvc_atomic_create(atom_i32, mtx, 0);

    // Increment the atomic integer by 5
    ldvc_atomic_inc(atom_i32, mtx, 5);
    std::cout << "After atomic increment: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Decrement the atomic integer by 1
    ldvc_atomic_dec(atom_i32, mtx, 1);
    std::cout << "After atomic DEC: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Increment the atomic integer by 2
    ldvc_atomic_inc(atom_i32, mtx, 2);
    std::cout << "After atomic INC: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Perform bitwise AND operation on the atomic integer with 2
    ldvc_atomic_and(atom_i32, mtx, 2);
    std::cout << "After atomic AND: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Perform bitwise OR operation on the atomic integer with 2
    ldvc_atomic_or(atom_i32, mtx, 2);
    std::cout << "After atomic OR: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Perform bitwise XOR operation on the atomic integer with 2
    ldvc_atomic_xor(atom_i32, mtx, 2);
    std::cout << "After atomic XOR: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Exchange the value of the atomic integer with 10 and retrieve the old value
    i32 old_val = ldvc_atomic_exchange(atom_i32, mtx, 10);
    std::cout << "After atomic exchange (old value): " << old_val << std::endl;
    std::cout << "After atomic exchange (new value): " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Load the current value of the atomic integer
    i32 loaded_val = ldvc_atomic_load(atom_i32, mtx);
    std::cout << "Current value after atomic load: " << loaded_val << std::endl;

    // Store a new value (20) into the atomic integer
    ldvc_atomic_store(atom_i32, mtx, 20);
    std::cout << "After atomic store: " << ldvc_atomic_load(atom_i32, mtx) << std::endl;

    // Delete the atomic integer
    ldvc_atomic_delete(atom_i32, mtx);
    std::cout << "Atomic value deleted." << std::endl;

    return 0;
}
