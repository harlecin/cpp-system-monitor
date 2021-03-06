#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid): 
    pid_(pid)
    ,user_(LinuxParser::User(pid))
    ,command_(LinuxParser::Command(pid))
    {}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    // Source calc: https://stackoverflow.com/a/16736599
    std::vector<long> stats = LinuxParser::StatParser(pid_);
    //TODO: Should I fetch system uptime from the system class instead?
    long uptime = LinuxParser::UpTime();
    long utime = stats[0];
    long stime = stats[1];
    long cutime = stats[2];
    long cstime = stats[3];
    long starttime = stats[4];

    // total time including child processes
    float total_time = utime + stime + cutime + cstime;
    float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));

    float cpu_util = 100 * ((total_time / sysconf(_SC_CLK_TCK)) / seconds);
    return cpu_util;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    std::vector<long> stats = LinuxParser::StatParser(pid_);
    long uptime_clock_ticks = stats[4];
    long uptime_sec = (uptime_clock_ticks)/sysconf(_SC_CLK_TCK);

    return uptime_sec;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }