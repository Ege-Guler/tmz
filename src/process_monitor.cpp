#include "../include/process_monitor.hpp"

ProcessMonitor::ProcessMonitor() {
    //processes = GetProcesses();
}

std::vector<ProcessMonitor::process> ProcessMonitor::GetProcesses() {
    std::vector<process> processes;


}

std::vector<int> ProcessMonitor::GetProcessesPID() {
    std::vector<int> pids;
    for (const auto &entry : std::filesystem::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string dir_name = entry.path().filename().string();
            if (std::all_of(dir_name.begin(), dir_name.end(), [](char c) { 
                return std::isdigit(c); 
            })) {
                pids.push_back(std::stoi(dir_name));
            }
        }
    }
    return pids;
}