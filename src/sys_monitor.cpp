#include "../include/sys_monitor.hpp"

SystemMonitor::SystemMonitor() {
    cpu_count = GetCpuCount();
}


// fetch cpu stats from /proc/stat
SystemMonitor::CpuStats SystemMonitor::GetCpuStats() {

    std::ifstream file("/proc/stat");
    std::string line;
    SystemMonitor::CpuStats stats{};

    if(std::getline(file, line)){
        std::istringstream ss(line);
        std::string cpu;

        ss >> cpu >> stats.user >> stats.nice >> stats.system >> stats.idle >> stats.iowait >> stats.irq >> stats.softirq >> stats.steal >> stats.guest >> stats.guest_nice;
    }
    
    return stats;
}

float SystemMonitor::CalculateCpuUsage() {

    SystemMonitor::CpuStats stats = GetCpuStats();
    static SystemMonitor::CpuStats prev_stats = stats;

    unsigned long long total = stats.user + stats.nice + stats.system + stats.idle + stats.iowait + stats.irq + stats.softirq + stats.steal + stats.guest + stats.guest_nice;
    unsigned long long prev_total = prev_stats.user + prev_stats.nice + prev_stats.system + prev_stats.idle + prev_stats.iowait + prev_stats.irq + prev_stats.softirq + prev_stats.steal + prev_stats.guest + prev_stats.guest_nice;

    unsigned long long totald = total - prev_total;
    unsigned long long idled = stats.idle - prev_stats.idle;

    prev_stats = stats;

    if (totald == 0) return 0.0f;
    return (totald - idled) * 100.0f / totald;

}

float SystemMonitor::GetCpuUsageBuffered(CircularBuffer<float> &cpu_buffer) {

    cpu_buffer.push(CalculateCpuUsage());
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return cpu_buffer.getAverage();

}

float SystemMonitor::GetMemoryUsage() {
    struct sysinfo info;
    sysinfo(&info);
    return (info.totalram - info.freeram) / (1024.0 * 1024.0);
}

// fetch system uptime and idle time from /proc/uptime
SystemMonitor::SysTime SystemMonitor::GetSysTime() {
    std::ifstream file("/proc/uptime");
    std::string line;
    SystemMonitor::SysTime systime{};

    if(std::getline(file, line)){
        std::istringstream ss(line);
        ss >> systime.uptime >> systime.idle;
    }

    return systime;
}

SystemMonitor::TimeBreakdown SystemMonitor::GetUpTime() {
   
    SystemMonitor::TimeBreakdown time{};
    double uptime = GetSysTime().uptime;

    time.hours = uptime / 3600;
    time.minutes = (uptime - time.hours * 3600) / 60;
    time.seconds = uptime - time.hours * 3600 - time.minutes * 60;

    return time;
}

// total idle time for all cpus 
// needs to be divided by the number of cpus to get the idle average I guess
SystemMonitor::TimeBreakdown SystemMonitor::GetIdleTime() {
   
    SystemMonitor::TimeBreakdown time{};
    double idle = GetSysTime().idle;

    time.hours = idle / 3600;
    time.minutes = (idle - time.hours * 3600) / 60;
    time.seconds = idle - time.hours * 3600 - time.minutes * 60;

    
    return time;
}

SystemMonitor::TimeBreakdown SystemMonitor::GetAvgIdleTime() {
    SystemMonitor::TimeBreakdown time{};
    double idle = GetSysTime().idle;

    idle /= this->cpu_count;

    time.hours = idle / 3600;
    time.minutes = (idle - time.hours * 3600) / 60;
    time.seconds = idle - time.hours * 3600 - time.minutes * 60;

    
    return time;
}

SystemMonitor::LoadAvg SystemMonitor::GetLoadAvg() {
    std::ifstream file("/proc/loadavg");
    std::string line;
    SystemMonitor::LoadAvg loadavg{};

    if(std::getline(file, line)){
        std::istringstream ss(line);
        ss >> loadavg.one_min >> loadavg.five_min >> loadavg.fifteen_min;
    }

    return loadavg;
}

unsigned int SystemMonitor::CpuCount() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    int cpu_count = 0;

    while(std::getline(file, line)){
        if(line.find("processor") != std::string::npos){
            ++cpu_count;
        }
    }

    return cpu_count;
}

unsigned int SystemMonitor::GetCpuCount() {
    return CpuCount();
}