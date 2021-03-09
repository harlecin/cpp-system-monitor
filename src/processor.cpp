#include "processor.h"

#include <unistd.h>

#include <vector>

#include "linux_parser.h"

float Processor::Utilization() {
  std::vector<long> Cpu = LinuxParser::CpuUtilization();

  if (Cpu.size() < 8) throw std::exception();
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

  float cpu_util = ((totald - idled) * 1.0f) / totald;

  return cpu_util;
}