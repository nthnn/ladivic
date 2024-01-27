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
#include <unistd.h>
#include <ldvc_ipc.hpp>

i32 main() {
    std::mutex mtx;

    i32 shmid = ldvc_create_ipc<i32>(mtx, "/tmp");
    if(shmid == -1)
        return 1;

    i32* data = ldvc_attach_ipc<i32>(shmid, mtx);
    if(!data) {
        ldvc_destroy_ipc<i32>(shmid, mtx);
        return 1;
    }
    *data = 0;

    pid_t pid = fork();
    if (pid == -1) {
        ldvc_detach_ipc<i32>(data, mtx);
        ldvc_destroy_ipc<i32>(shmid, mtx);

        std::cerr << "Fork error!" << std::endl;
        return 1;
    }

    if (pid == 0) {
        for(u8 i = 0; i < 5; i++) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                ++(*data);
            }

            std::cout << "Child: Incremented shared value to " << *data << std::endl;
            sleep(1);
        }
    } else {
        for(u8 i = 0; i < 5; i++) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                std::cout << "Parent: Shared value is " << *data << std::endl;
            }
            sleep(1);
        }
    }

    ldvc_detach_ipc<i32>(data, mtx);
    ldvc_destroy_ipc<i32>(shmid, mtx);

    return 0;
}
