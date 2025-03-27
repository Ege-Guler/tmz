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

    struct LoadAvg
    {
        float one_min, five_min, fifteen_min;
    };

    SystemMonitor();

    float GetCpuUsageBuffered(CircularBuffer<float> &cpu_buffer);
    float GetMemoryUsage();

    TimeBreakdown GetUpTime();
    TimeBreakdown GetIdleTime();
    TimeBreakdown GetAvgIdleTime();

    LoadAvg GetLoadAvg();

    // getters
    unsigned int GetCpuCount();
    
private:
    float CalculateCpuUsage();
    CpuStats GetCpuStats();
    SysTime GetSysTime();
    unsigned int CpuCount();


    // vars
    unsigned int cpu_count;

    
    
};

#endif // SYS_MONITOR_HPP
