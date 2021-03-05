#include "processor.h"
#include "linux_parser.h"
#include<vector>
#include<unistd.h>

float Processor::Utilization() { 
    std::vector<long> CpuPrev = LinuxParser::CpuUtilization();
    sleep(1);
    std::vector<long> Cpu = LinuxParser::CpuUtilization();

    // Source CPU Utilization calc: https://stackoverflow.com/a/23376195
    long PrevIdle = CpuPrev[3] + CpuPrev[4];
    long Idle = Cpu[3] + Cpu[4];
    
    long PrevNonIdle = CpuPrev[0] + CpuPrev[1] + CpuPrev[2] + CpuPrev[5] + CpuPrev[6] + CpuPrev[7];
    long NonIdle = Cpu[0] + Cpu[1] + Cpu[2] + Cpu[5] + Cpu[6] + Cpu[7];

    long PrevTotal = PrevIdle + PrevNonIdle;
    long Total = Idle + NonIdle;

    long idled = Idle - PrevIdle;
    long totald = Total - PrevTotal;
    float cpu_util = ((totald - idled)*1.0)/(totald*1.0);

    return cpu_util;
}