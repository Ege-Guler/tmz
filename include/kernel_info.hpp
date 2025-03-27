#ifndef KERNEL_INFO_HPP
#define KERNEL_INFO_HPP

#include <string>
#include <fstream>
#include <sstream>

class KernelInfo {
public:
    KernelInfo() = delete;
    static std::string GetKernelVersion();
private:
};

#endif // KERNEL_INFO_HPP