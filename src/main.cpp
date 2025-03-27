#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "../include/sys_monitor.hpp"
#include "../utils/circular_buffer.hpp"
#include "../include/kernel_info.hpp"
#include <thread>
#include <chrono>

using namespace ftxui;

// Circular buffer to store CPU usage values
CircularBuffer<float> cpu_buffer(8);

std::string GetStats(SystemMonitor &monitor) {

    return "CPU Usage: " + std::to_string(monitor.GetCpuUsageBuffered(cpu_buffer)) + "%\n"
           "Memory Usage: " + std::to_string(monitor.GetMemoryUsage()) + "MB";
}

std::string GetHeader() {
    return "System Monitor - Kernel Version: " + KernelInfo::GetKernelVersion();
}

std::string GetSysTimeStr(SystemMonitor &monitor) {
    auto uptime = monitor.GetUpTime();
    auto idle = monitor.GetIdleTime();

    return "Uptime: " + std::to_string(uptime.hours) + "h " + std::to_string(uptime.minutes) + "m " + std::to_string(uptime.seconds) + "s\n"
           "Idle Time: " + std::to_string(idle.hours) + "h " + std::to_string(idle.minutes) + "m " + std::to_string(idle.seconds) + "s";
}

int main() {
    
    SystemMonitor monitor;

    auto screen = ScreenInteractive::Fullscreen();

    std::string stats = GetStats(monitor);
    std::string header = GetHeader();
    std::string sys_time = GetSysTimeStr(monitor);

    auto system_stats = Renderer([&] {
        return vbox({
            text(header),
            separator(),
            text(stats),
            separator(),
            text(sys_time),
        }) | border;
    });

    std::thread([&] {
        while (true) {

             // update cached strings
            stats = GetStats(monitor);
            sys_time = GetSysTimeStr(monitor);

            // force refresh
            screen.PostEvent(Event::Custom); 
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }).detach();

    screen.Loop(system_stats);


    return 0;
}
