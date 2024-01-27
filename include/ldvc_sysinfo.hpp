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
 * @file ldvc_sysinfo.hpp
 * @brief Provides utilities for retrieving system information.
 *
 * This header file contains functions for retrieving various system information,
 * including CPU information, total memory, and available disk space.
 * 
 * @author Nathanne Isip
 * 
 */

#ifndef LDVC_SYSINFO_HPP
#define LDVC_SYSINFO_HPP

#include <ldvc_type.hpp>

/**
 * 
 * @brief Retrieves CPU information.
 *
 * This function retrieves information about the CPU,
 * such as the model, architecture, and other relevant
 * details.
 *
 * @return A string containing CPU information.
 * 
 */
string ldvc_cpu_info();

/**
 * 
 * @brief Retrieves the total amount of memory installed on the system.
 *
 * This function retrieves the total amount of memory installed on the system,
 * typically expressed in bytes.
 *
 * @return The total amount of memory installed on the system.
 * 
 */
u64 ldvc_total_memory();

/**
 * 
 * @brief Retrieves available disk space.
 *
 * This function retrieves information about the available disk space on the system,
 * typically expressed in bytes.
 *
 * @return The available disk space on the system.
 * 
 */
u64 ldvc_disk_space();

#endif