#include "../include/kernel_info.hpp"

std::string KernelInfo::GetKernelVersion() {
    std::ifstream file("/proc/version");
    std::string line;
    std::getline(file, line);

    std::istringstream ss(line);
    std::string linux_str, version_str, version_number;

    ss >> linux_str >> version_str >> version_number;
    
    return version_number;
}