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
 * @file ldvc_type.hpp
 * @brief Defines common types used throughout the library.
 *
 * This header file defines several common types used throughout the library,
 * including integer types, floating-point types, string type, and other aliases.
 * 
 * @author Nathanne Isip
 * 
 */
#ifndef LDVC_TYPE_HPP
#define LDVC_TYPE_HPP

#include <string>
#include <cstdint>

/// Alias for std::string
using string    = std::string;

/// Alias for a Unicode character
using rune      = char;

/// Signed integer types
using i8        = signed char;
using i16       = short;
using i32       = int;
using i64       = long long;

/// Unsigned integer types
using u8        = unsigned char;
using u16       = unsigned short;
using u32       = unsigned int;
using u64       = unsigned long long;

/// Floating-point type
using real      = double;

/// Unsigned size type
using usize     = size_t;

/// Alias for void pointer
using any       = void*;

#endif