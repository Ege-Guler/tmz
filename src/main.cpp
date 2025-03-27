#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <chrono>


#include "../include/sys_monitor.hpp"
#include "../utils/circular_buffer.hpp"
#include "../include/kernel_info.hpp"
#include "../include/formatter.hpp"

using namespace ftxui;

// Circular buffer to store CPU usage values
CircularBuffer<float> cpu_buffer(8);

int main() {
    
    SystemMonitor monitor;

    auto screen = ScreenInteractive::Fullscreen();

    std::string cpu_stats = Formatter::FormatCpu(monitor, cpu_buffer);
    std::string header = Formatter::FormatHeader();
    std::string sys_time = Formatter::FormatSysTime(monitor);
    std::string load_avg = Formatter::FormatLoadAvg(monitor);
    std::string cpu_count = Formatter::FormatCpuCount(monitor);


    auto system_stats = Renderer([&] {
        return vbox({
            text(header),
            separator(),
            text(cpu_stats),
            separator(),
            text(sys_time),
            separator(),
            text(load_avg),
            separator(),
            text(cpu_count),
        }) | border;
    });

    std::thread([&] {
        while (true) {

             // update cached strings
            cpu_stats = Formatter::FormatCpu(monitor, cpu_buffer);
            sys_time = Formatter::FormatSysTime(monitor);
            load_avg = Formatter::FormatLoadAvg(monitor);

            // force refresh
            screen.PostEvent(Event::Custom); 
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }).detach();

    screen.Loop(system_stats);


    return 0;
}
