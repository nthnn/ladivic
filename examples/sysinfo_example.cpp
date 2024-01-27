#include <iostream>
#include <string>
#include <ldvc_sysinfo.hpp>

i32 main() {
    std::cout << "CPU Information: " << ldvc_cpu_info() << std::endl;
    std::cout << "Number of CPU cores: " << ldvc_cpu_cores() << std::endl;
    std::cout << "Total Memory: " << ldvc_total_memory() / 1024 / 1024 << " MBytes" << std::endl;
    std::cout << "Disk Space Available: " << ldvc_disk_space() << " bytes" << std::endl;

    return 0;
}
