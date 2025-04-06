#include "../include/formatter.hpp"


std::string Formatter::FormatCpu(SystemMonitor &monitor, CircularBuffer<float> &cpu_buffer) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(PRECISION);
    ss << "CPU Usage: " << monitor.GetCpuUsageBuffered(cpu_buffer) << "% ";
    return ss.str();

}

std::string Formatter::FormatMemory(SystemMonitor &monitor) {
    std::ostringstream ss;
    ss << "Memory Usage: " << monitor.GetMemoryUsage() << "MB ";
    return ss.str();
}

std::string Formatter::FormatSysTime(SystemMonitor &monitor) {

    std::ostringstream ss;
    auto uptime = monitor.GetUpTime();
    auto idle = monitor.GetIdleTime();

    ss << "Uptime: " << uptime.hours << "h " << uptime.minutes << "m " << uptime.seconds << "s "
       << "Idle Time: " << idle.hours << "h " << idle.minutes << "m " << idle.seconds << "s ";
    
    return ss.str();
}

std::string Formatter::FormatHeader() {
    std::ostringstream ss;
    ss << "System Monitor - Kernel Version: " << KernelInfo::GetKernelVersion();
    return ss.str();

}

std::string Formatter::FormatKernelVersion() {
    std::ostringstream ss;
    ss << "Kernel Version: " << KernelInfo::GetKernelVersion();
    return ss.str();
}

std::string Formatter::FormatUptime(SystemMonitor &monitor) {
    std::ostringstream ss;
    auto uptime = monitor.GetUpTime();

    ss << "Uptime: " << uptime.hours << "h " << uptime.minutes << "m " << uptime.seconds << "s ";
    return ss.str();
}

std::string Formatter::FormatIdleTime(SystemMonitor &monitor) {
    std::ostringstream ss;
    auto idle = monitor.GetIdleTime();
    ss << "Idle Time: " << idle.hours << "h " << idle.minutes << "m " << idle.seconds << "s ";
    return ss.str();
}

std::string Formatter::FormatAvgIdleTime(SystemMonitor &monitor) {
    std::ostringstream ss;
    auto idle = monitor.GetAvgIdleTime();
    ss << "Average Idle Time: " << idle.hours << "h " << idle.minutes << "m " << idle.seconds << "s ";
    return ss.str();
}


std::string Formatter::FormatLoadAvg(SystemMonitor &monitor) {
    std::ostringstream ss;
    auto loadAvg = monitor.GetLoadAvg();
    ss << "Load Average: " << loadAvg.one_min << " " << loadAvg.five_min << " " << loadAvg.fifteen_min;
    return ss.str();
}

std::string Formatter::FormatCpuCount(SystemMonitor &monitor) {
    std::ostringstream ss;
    ss << "CPU Count: " << monitor.GetCpuCount();
    return ss.str();
}

std::string Formatter::FormatProcessesPID(ProcessMonitor &process_monitor) {
    std::ostringstream ss;
    std::vector<int> pids = process_monitor.GetProcessesPID();
    ss << "Processes PIDs: ";

    //!TODO correct the formatting later
    for (const int &pid : pids) {
        ss << pid << " ";
    }
    ss << std::endl;
    
    return ss.str();
}