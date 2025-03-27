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

    struct SysTime
    {
        double uptime; 
        double idle;
    };

    struct CpuStats
    {
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
    };

    struct TimeBreakdown
    {
        unsigned int hours, minutes,seconds;
    };

    float GetCpuUsageBuffered(CircularBuffer<float> &cpu_buffer);
    float GetMemoryUsage();
    float CalculateCpuUsage();
    TimeBreakdown GetUpTime();
    TimeBreakdown GetIdleTime();
    
    
private:
    CpuStats GetCpuStats();
    SysTime GetSysTime();
    
};

#endif // SYS_MONITOR_HPP
