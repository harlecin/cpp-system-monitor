#pragma once

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<( Process& a);             

  // TODO: Declare any necessary private members
 private:
    int pid_;
    std::string uid_;
    std::string user_;
    std::string command_;
};