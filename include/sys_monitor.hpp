#ifndef SYS_MONITOR_HPP
#define SYS_MONITOR_HPP

#include "../utils/circular_buffer.hpp"
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>

#ifdef __linux__
#include <sys/sysinfo.h>
#endif

class SystemMonitor {
public:
    float GetCpuUsageBuffered(CircularBuffer<float> &cpu_buffer);
    float GetMemoryUsage();
    float CalculateCpuUsage();
    struct CpuStats
    {
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    };
private:
    CpuStats GetCpuStats();
    
};

#endif // SYS_MONITOR_HPP
