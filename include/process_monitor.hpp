#ifndef PROCESS_MONITOR_HPP
#define PROCESS_MONITOR_HPP
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <algorithm>

class ProcessMonitor {

    public:
    
    struct process
    {
        unsigned int pid;
        std::string name;
        char state;
        int thread_count;
        unsigned int ppid;
    
        float mem_usage;
        float cpu_usage;
    
        std::string user;
        std::string group;
    
    };
    
        ProcessMonitor();
        std::vector<process> GetProcesses();
        std::vector<int> GetProcessesPID();
    
    private:
        std::vector<process> processes;
    };

#endif // PROCESS_MONITOR_HPP