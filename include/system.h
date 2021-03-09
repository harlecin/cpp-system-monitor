#pragma once

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();                   
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string os_;
  std::string kernel_;
};