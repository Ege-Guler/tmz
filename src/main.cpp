#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include "../include/sys_monitor.hpp"
#include "../utils/circular_buffer.hpp"
#include <thread>
#include <chrono>

using namespace ftxui;

// Circular buffer to store CPU usage values
CircularBuffer<float> cpu_buffer(8);

std::string GetStats(SystemMonitor &monitor) {

    return "CPU Usage: " + std::to_string(monitor.GetCpuUsageBuffered(cpu_buffer)) + "%\n"
           "Memory Usage: " + std::to_string(monitor.GetMemoryUsage()) + "MB";
}

int main() {
    SystemMonitor monitor;
    auto screen = ScreenInteractive::Fullscreen();

    std::string stats = GetStats(monitor);
    auto system_stats = Renderer([&] {
        return vbox({
            text("System Monitor"),
            separator(),
            text(stats),
        }) | border;
    });

    std::thread([&] {
        while (true) {
            stats = GetStats(monitor); // update cached string
            screen.PostEvent(Event::Custom); // manual redraw
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }).detach();

    screen.Loop(system_stats);


    return 0;
}
