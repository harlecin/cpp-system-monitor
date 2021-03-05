#include "processor.h"
#include "linux_parser.h"
#include<vector>
#include<unistd.h>

float Processor::Utilization() { 
    std::vector<long> CpuPrev = LinuxParser::CpuUtilization();
    sleep(1);
    std::vector<long> Cpu = LinuxParser::CpuUtilization();

    // Source CPU Utilization calc: https://stackoverflow.com/a/23376195
    long user = Cpu[0];
    long nice = Cpu[1];
    long system = Cpu[2];
    long idle = Cpu[3];
    long iowait = Cpu[4];
    long irq = Cpu[5];
    long softirq = Cpu[6];
    long steal = Cpu[7];

    long Idle = idle + iowait;
    long NonIdle = user + nice + system + irq + softirq + steal;

    long Total = Idle + NonIdle;

    long idled = Idle - this->PrevIdle;
    long totald = Total - this->PrevTotal;

    this->PrevIdle = Idle;
    this->PrevTotal = Total;

    float cpu_util = ((totald - idled)*1.0)/totald;

    return cpu_util;
}