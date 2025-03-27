#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <sstream>
#include <iomanip>

#include "../include/sys_monitor.hpp"
#include "../include/kernel_info.hpp"


// fp precision
#define PRECISION 2

class Formatter {
public:
    Formatter() = delete;

    static std::string FormatCpu(SystemMonitor &monitor, CircularBuffer<float> &cpu_buffer);
    static std::string FormatMemory(SystemMonitor &monitor);
    static std::string FormatSysTime(SystemMonitor &monitor);
    static std::string FormatHeader();
    static std::string FormatKernelVersion();
    static std::string FormatUptime(SystemMonitor &monitor);
    static std::string FormatIdleTime(SystemMonitor &monitor);
};




#endif // FORMATTER_HPP