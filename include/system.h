#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "process_parser.h"
#include "util.h"

class System {
 public:
  System();
  void Refresh();
  void setLastCpuMeasures();
  std::string MemoryUtilization() const;
  long UpTime() const;
  std::string Threads() const;
  std::string TotalProcesses() const;
  std::string RunningProcesses() const;
  std::string Kernel() const;
  std::string OperatingSystem() const;
  std::string AggregateCpuUtilization();
  std::vector<std::string> IndividualCpuUtilizations();
  void getOtherCores(int size);
  void setCpuCoresStats();

 private:
  std::vector<std::string> cached_aggregate_cpu_times_;
  std::vector<std::vector<std::string>> cached_individual_cpu_times_;
  std::vector<std::vector<std::string>> cached_cpu_times_;
  std::vector<std::string> currentCpuStats;
  std::vector<std::string> coresStats;
  std::vector<std::vector<std::string>> lastCpuCoresStats;
  std::vector<std::vector<std::string>> currentCpuCoresStats;
  std::string cpu_{-1};
  float memPercent;
  std::string os_name_;
  std::string kernel_version_;
  long up_time_;
  int total_procs_;
  int running_proc_;
  int threads_;
};

#endif