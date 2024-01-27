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

#ifdef __linux__
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#elif __APPLE__
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/param.h>
#include <sys/mount.h>
#endif

#include <string>
#include <thread>
#include <ldvc_sysinfo.hpp>

string ldvc_cpu_info() {
#ifdef __linux__
    return std::to_string(get_nprocs());
#elif __APPLE__
    usize len = 100;
    rune cpu_info[100];
    sysctlbyname("machdep.cpu.brand_string", &cpu_info, &len, NULL, 0);

    return std::string(cpu_info);
#else
    return "Unsupported platform";
#endif
}

u64 ldvc_total_memory() {
#ifdef __linux__
    struct sysinfo mem_info;
    sysinfo(&mem_info);

    return (u64) (mem_info.totalram * mem_info.mem_unit);
#elif __APPLE__
    usize len = 100;
    u64 total_mem;

    sysctlbyname("hw.memsize", &total_mem, &len, NULL, 0);
    return total_mem;
#else
    return 0;
#endif
}

u64 ldvc_disk_space() {
#ifdef __linux__
    struct statvfs buf;
    statvfs("/", &buf);

    return (u64) (buf.f_bavail * buf.f_frsize);
#elif __APPLE__
    struct statfs buf;
    statfs("/", &buf);

    return (u64) (buf.f_bavail * buf.f_bsize);
#else
    return 0;
#endif
}

u32 ldvc_cpu_cores() {
    return std::thread::hardware_concurrency();
}