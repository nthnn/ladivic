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
 * @file ldvc_async.hpp
 * @brief Provides utilities for asynchronous execution in C++.
 *
 * This header file defines functions for executing tasks asynchronously in C++,
 * providing capabilities for delayed execution and timeout handling.
 *
 * @author Nathanne Isip
 * 
 */

#ifndef LDVC_ASYNC_HPP
#define LDVC_ASYNC_HPP

#include <future>

/**
 * 
 * @brief Executes a function asynchronously.
 *
 * This function executes the given function `f` asynchronously, along with its
 * arguments `args`. It returns a std::future object representing the result
 * of the function call.
 *
 * @tparam F The type of the function to be executed.
 * @tparam A The types of the arguments to the function.
 * 
 * @param f The function to be executed.
 * @param args The arguments to the function.
 * 
 * @return std::future<typename std::result_of<F(A...)>::type> A future object
 *         representing the result of the function call.
 * 
 */
template<typename F, typename... A>
std::future<typename std::result_of<F(A...)>::type> ldvc_async_execute(F&& f, A&&... args)
{
    using return_type = typename std::result_of<F(A...)>::type;

    std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<A>(args)...));
    std::future<return_type> result = task.get_future();
    std::thread(std::move(task)).detach();

    return result;
}

/**
 * 
 * @brief Executes a function asynchronously with a delay.
 *
 * This function executes the given function `f` asynchronously, along with its
 * arguments `args`, after the specified delay. It returns a std::future object
 * representing the result of the function call.
 *
 * @tparam R The type of the delay duration.
 * @tparam P The type of the delay duration.
 * @tparam F The type of the function to be executed.
 * @tparam A The types of the arguments to the function.
 * 
 * @param delay The delay duration before executing the function.
 * @param f The function to be executed.
 * @param args The arguments to the function.
 * 
 * @return std::future<typename std::result_of<F(A...)>::type> A future object
 *         representing the result of the function call.
 * 
 */
template<typename R, typename P, typename F, typename... A>
std::future<typename std::result_of<F(A...)>::type> ldvc_async_execute_with_delay(
    const std::chrono::duration<R, P>& delay,
    F&& f,
    A&&... args
)
{
    return std::async(std::launch::async, [=]() {
        std::this_thread::sleep_for(delay);
        return f(std::forward<A>(args)...);
    });
}

/**
 * 
 * @brief Executes a function asynchronously with a timeout.
 *
 * This function executes the given function `f` asynchronously, along with its
 * arguments `args`, and provides a timeout mechanism. If the function does not
 * complete within the specified timeout duration, an exception is thrown.
 *
 * @tparam R The type of the timeout duration.
 * @tparam P The type of the timeout duration.
 * @tparam F The type of the function to be executed.
 * @tparam A The types of the arguments to the function.
 * 
 * @param timeout The timeout duration for the function execution.
 * @param f The function to be executed.
 * @param args The arguments to the function.
 * 
 * @return std::future<typename std::result_of<F(A...)>::type> A future object
 *         representing the result of the function call.
 * 
 * @throw std::runtime_error Thrown if the function execution exceeds the
 *        specified timeout duration.
 * 
 */
template<typename R, typename P, typename F, typename... A>
std::future<typename std::result_of<F(A...)>::type> ldvc_async_execute_with_timeout(
    const std::chrono::duration<R, P>& timeout,
    F&& f,
    A&&... args
)
{
    std::promise<typename std::result_of<F(A...)>::type> promise;
    std::future<typename std::result_of<F(A...)>::type> result = promise.get_future();

    std::thread([=, &promise]() {
        try {
            f(std::forward<A>(args)...);
        } catch (...) {
            promise.set_exception(std::current_exception());
            return;
        }
        promise.set_value();
    }).detach();

    std::thread([=, &promise]() {
        std::this_thread::sleep_for(timeout);
        promise.set_exception(std::make_exception_ptr(std::runtime_error("Timeout")));
    }).detach();

    return result;
}

#endif