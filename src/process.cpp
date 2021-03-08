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

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { 
    // Source calc: https://stackoverflow.com/a/16736599
    long uptime = LinuxParser::UpTime();
    std::vector<long> stats = LinuxParser::StatParser(pid_);
    //TODO: Should I fetch system uptime from the system class instead?
    long utime = stats[0];
    long stime = stats[1];
    long cutime = stats[2];
    long cstime = stats[3];
    long starttime = stats[4];

    // total time including child processes
    float total_time = utime + stime + cutime + cstime;
    long process_uptime = uptime - (starttime / sysconf(_SC_CLK_TCK));

    float cpu_util =  ((total_time / sysconf(_SC_CLK_TCK)) / process_uptime);
    return cpu_util;
}

string Process::Command() { return command_; }

string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return user_; }

long int Process::UpTime() { 
    long sys_uptime = LinuxParser::UpTime();
    std::vector<long> stats = LinuxParser::StatParser(pid_);
    long start_clock_ticks = stats[0] + stats[1] + stats[2] + stats[3];
    long uptime_sec = sys_uptime - (start_clock_ticks)/sysconf(_SC_CLK_TCK);

    return uptime_sec;
}

bool Process::operator<(Process a)  {
  return this->CpuUtilization() > a.CpuUtilization();
}