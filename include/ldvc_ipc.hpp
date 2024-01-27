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
 * @file ldvc_ipc.hpp
 * @brief Provides utilities for Inter-Process Communication (IPC) using shared memory.
 *
 * This header file contains a set of functions for managing shared memory segments
 * to facilitate inter-process communication (IPC). These functions enable the creation,
 * attachment, detachment, and destruction of shared memory segments, ensuring thread safety
 * during these operations.
 * 
 * @author Nathanne Isip
 * 
 */
#ifndef LDVC_IPC_HPP
#define LDVC_IPC_HPP

#include <sys/ipc.h>
#include <sys/shm.h>
#include <ldvc_type.hpp>

/**
 * 
 * @brief Creates a new IPC shared memory segment.
 *
 * This function creates a new IPC shared memory segment with the specified
 * size and a unique key derived from the provided path.
 *
 * @tparam T The type of data to be stored in the shared memory segment.
 * 
 * @param mtx A mutex used to ensure thread safety during the creation process.
 * @param path The path used to generate the unique key for the shared memory segment.
 * 
 * @return The shared memory identifier (shmid) on success, or -1 on failure.
 * 
 */
template<typename T>
i32 ldvc_create_ipc(std::mutex& mtx, string path)
{
    std::lock_guard<std::mutex> lock(mtx);

    key_t key = ftok(path.c_str(), 'A');
    if(key == -1)
        return -1;

    return shmget(key, sizeof(T), 0666 | IPC_CREAT);
}

/**
 * 
 * @brief Attaches to an existing IPC shared memory segment.
 *
 * This function attaches to an existing IPC shared memory segment
 * specified by its identifier (shmid).
 *
 * @tparam T The type of data stored in the shared memory segment.
 * 
 * @param shmid The identifier of the shared memory segment to attach to.
 * @param mtx A mutex used to ensure thread safety during the attachment process.
 * 
 * @return A pointer to the shared memory region on success, or nullptr on failure.
 * 
 */
template<typename T>
T* ldvc_attach_ipc(i32 shmid, std::mutex& mtx)
{
    std::lock_guard<std::mutex> lock(mtx);

    any ptr = shmat(shmid, nullptr, 0);
    if(ptr == (any) -1)
        return nullptr;

    return static_cast<T*>(ptr);
}

/**
 * 
 * @brief Detaches from an IPC shared memory segment.
 *
 * This function detaches from an IPC shared memory segment
 * given a pointer to the shared memory region.
 *
 * @tparam T The type of data stored in the shared memory segment.
 * 
 * @param data A pointer to the shared memory region.
 * @param mtx A mutex used to ensure thread safety during the detachment process.
 * 
 * @return 0 on success, or -1 on failure.
 * 
 */
template<typename T>
u8 ldvc_detach_ipc(T* data, std::mutex& mtx)
{
    std::lock_guard<std::mutex> lock(mtx);

    if(shmdt(data) == -1)
        return -1;
    return 0;
}

/**
 * 
 * @brief Destroys an IPC shared memory segment.
 *
 * This function destroys an IPC shared memory segment specified by
 * its identifier (shmid).
 *
 * @tparam T The type of data stored in the shared memory segment.
 * 
 * @param shmid The identifier of the shared memory segment to destroy.
 * @param mtx A mutex used to ensure thread safety during the destruction process.
 * 
 * @return True if the destruction was successful, false otherwise.
 * 
 */
template<typename T>
bool ldvc_destroy_ipc(i32 shmid, std::mutex& mtx)
{
    std::lock_guard<std::mutex> lock(mtx);
    return shmctl(shmid, IPC_RMID, nullptr) == -1;
}

#endif