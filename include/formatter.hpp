#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <sstream>
#include <iomanip>

#include "../include/sys_monitor.hpp"
#include "../include/kernel_info.hpp"
#include "../include/process_monitor.hpp"

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
    static std::string FormatAvgIdleTime(SystemMonitor &monitor);
    static std::string FormatLoadAvg(SystemMonitor &monitor);
    static std::string FormatCpuCount(SystemMonitor &monitor);
    static std::string FormatProcessesPID(ProcessMonitor &process_monitor);
    static std::string FormatProcesses(ProcessMonitor &process_monitor, int max_processes = 10);
};




#endif // FORMATTER_HPP