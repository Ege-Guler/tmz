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
    
    //https://stackoverflow.com/questions/39066998/what-are-the-meaning-of-values-at-proc-pid-stat
    struct process
    {
        // /proc/[pid]/stat

        int pid;                        // (1)
        std::string comm;               // (2)
        char state;                     // (3)
        int ppid;                       // (4)

        unsigned long utime;            // (14)
        unsigned long stime;            // (15)

        long cutime;                    // (16)
        long cstime;                    // (17)

        long priority;                  // (18)
        long nice;                      // (19)

        long num_threads;               // (20)

        unsigned long long starttime;   // (21)

        unsigned long vsize;            // (23)
        long rss;                       // (24)
        
        int processor;                  // (39)

        // proc/[pid]/status

        std::vector<std::string> user;
        std::vector<std::string> group;
    
    };
    
        ProcessMonitor();
        std::vector<process> GetProcesses();
        std::vector<int> GetProcessesPID();
    
    private:
        std::vector<process> processes;
    };

#endif // PROCESS_MONITOR_HPP