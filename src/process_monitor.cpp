#include "../include/process_monitor.hpp"

ProcessMonitor::ProcessMonitor() {
    //processes = GetProcesses();
}

std::vector<ProcessMonitor::process> ProcessMonitor::GetProcesses() {

    const auto &pids = ProcessMonitor::GetProcessesPID();

    for(const auto &pid : pids) {
        
        // Read /proc/[pid]/stat
        std::ifstream file("/proc/" + std::to_string(pid) + "/stat");
        if (!file.is_open()) {
            // Skip if the file cannot be opened
            //!TODO add logging
            continue;
        }

        std::string line;
        if(!std::getline(file, line)){
            // Skip if the line cannot be read
            //!TODO add logging
            continue;
        }

        std::istringstream ss(line);

        process proc;

        ss >> proc.pid >> proc.comm >> proc.state >> proc.ppid;

        for(int i = 0; i < 9; ++i) {
            std::string temp;
            ss >> temp;
        }

        ss >> proc.utime >> proc.stime >> proc.cutime >> proc.cstime;
        ss >> proc.priority >> proc.nice >> proc.num_threads >> proc.starttime;
        ss >> proc.vsize >> proc.rss;

        for(int i = 0; i < 14; ++i) {
            std::string temp;
            ss >> temp;
        }
        ss >> proc.processor;

        // Read /proc/[pid]/status for user and group
        
        std::ifstream status_file("/proc/" + std::to_string(pid) + "/status");
        if(!file.is_open()){
            // Skip if the file cannot be opened
            //!TODO add logging
            continue;
        }
        std::string status_line;
        while(std::getline(status_file, status_line)){
            if(status_line.find("Uid:") != std::string::npos){
                std::istringstream status_ss(status_line);
                std::string token;
                while(status_ss >> token) {
                    if (token == "Uid:") {
                        continue;
                    }
                    proc.user.push_back(token);
                }
            }
            if(status_line.find("Gid:") != std::string::npos){
                std::istringstream status_ss(status_line);
                std::string token;
                while(status_ss >> token) {
                    if (token == "Gid:") {
                        continue;
                    }
                    proc.group.push_back(token);
                }
            }
        }

        processes.push_back(proc);
    }
    return processes;



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

