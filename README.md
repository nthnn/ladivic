## ladivic

![Build Test](https://github.com/nthnn/ladivic/actions/workflows/build_test.yml/badge.svg)
![GitHub repo size](https://img.shields.io/github/repo-size/nthnn/ladivic?logo=git&label=Repository%20Size)

Ladivic is a C++ library designed to provide system-level thread- and fail-safe functions. It offers various functionalities related to asynchronous operations, atomic operations, input/output operations, inter-process communication (IPC), memory management, and system information retrieval. The library aims to simplify system-level programming tasks by providing robust and reliable functions that ensure thread safety and error handling. Hence, Ladivic stands as a versatile and indispensable asset for tackling complex system-level challenges with confidence and efficiency.

```cpp
#include <ldvc_mem.hpp>
#include <ldvc_type.hpp>

#include <iostream>

using namespace std;

i32 main() {
    i32* i32_array = ldvc_malloc<i32>(5);
    for(usize i = 0; i < 5; ++i)
        i32_array[i] = static_cast<i32>(i * 10);

    cout << "Original Array: ";
    for(usize i = 0; i < 5; ++i)
        std::cout << i32_array[i] << " ";
    cout << endl;
}
```

## Features

### Asynchronous Operations

Ladivic facilitates seamless execution of asynchronous tasks with its suite of functions designed to handle concurrency elegantly. Developers can leverage `ldvc_async_execute` to execute functions asynchronously, providing a future object for result retrieval. Additionally, tasks can be scheduled with specified delays or timeouts using `ldvc_async_execute_with_delay` and `ldvc_async_execute_with_timeout`, enabling precise control over task execution in multithreaded environments.

### Atomic Operations

Thread safety is paramount in system-level programming, and Ladivic delivers robust atomic operations to ensure data integrity in concurrent scenarios. With functions for atomic increment, decrement, exchange, load, store, and bitwise operations (AND, OR, XOR), developers can manipulate variables atomically with ease, safeguarding against race conditions and data corruption.

### Input/Output Operations

Efficient handling of input/output operations is critical for system-level applications, and Ladivic streamlines this process with its input/output module. Developers can effortlessly read and write data to files using `ldvc_io.hpp`, with additional support for checking file existence and creating folders seamlessly, enhancing file management capabilities in system-level applications.

### Inter-Process Communication (IPC)

Facilitating communication between processes is essential for building robust system-level applications, and Ladivic simplifies this process with its IPC module. By providing functions for creating, attaching, detaching, and destroying shared memory segments, Ladivic empowers developers to implement efficient inter-process communication mechanisms, enabling seamless data exchange and synchronization between processes.

### Memory Management

Effective memory management is fundamental for optimizing system-level applications, and Ladivic offers powerful memory management functionalities to address this need. Developers can safely allocate and deallocate memory using thread-safe functions in the `ldvc_mem.hpp` module, ensuring efficient utilization of system resources and minimizing memory-related issues.

### System Information Retrieval

Accessing essential system information is vital for system-level applications, and Ladivic simplifies this process with its system information retrieval module. Developers can retrieve critical system information such as CPU details, total memory, and disk space using functions in the `ldvc_sysinfo.hpp` module, enabling comprehensive system monitoring and analysis capabilities.

## Installation

To incorporate Ladivic into your C++ project, follow these simple steps:

1. Clone the Ladivic repository to your local machine:

```bash
git clone https://github.com/nthnn/ladivic.git
```

2. Include the necessary header files in your C++ code:

```cpp
#include "ldvc_async.hpp"
#include "ldvc_atomic.hpp"
#include "ldvc_io.hpp"
#include "ldvc_ipc.hpp"
#include "ldvc_mem.hpp"
#include "ldvc_sysinfo.hpp"
#include "ldvc_type.hpp"
```

3. During compilation, ensure the Ladivic library is linked to your project.

Or, you can compile the [examples](examples) by:

```bash
qrepo run build
```

Just make sure you have [Qrepo](https://github.com/nthnn/Qrepo) and [CMake](https://cmake.org) installed on your system.

## Contributing

Contributions to Ladivic are highly encouraged and appreciated! To contribute new features, bug fixes, or enhancements, please adhere to the following guidelines:

1. Fork the Ladivic repository.
2. Create a new branch for your changes: `git checkout -b feature-name`.
3. Implement your changes and commit them: `git commit -m "Added new feature"`.
4. Push your changes to the branch: `git push origin feature-name`.
5. Submit a pull request for review and inclusion.

## License

Ladivic is distributed under the GNU General Public License v3.0. For further details, refer to the [LICENSE](https://github.com/nthnn/ladivic/tree/main/LICENSE) file.