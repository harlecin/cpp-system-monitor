#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // pull of the tokens from linestream:
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem (available from c++17)
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() { 
    long free_memory = 0;
    long total_memory = 0;
    string key; 
    long value;
    string line;

    std::ifstream stream(kProcDirectory + kMeminfoFilename);
    if (stream.is_open()) {
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        linestream >> key >> value;
          if (key == "MemTotal:") {
            total_memory = value;
          }
          if (key == "MemFree:") {
            free_memory = value;
          }
      }
    }

  long used_mem = total_memory - free_memory;
  float mem_util = (used_mem*1.0)/(total_memory*1.0); 
  return mem_util;
}

long LinuxParser::UpTime() { 
    long total_uptime;
    string line;

    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);

      linestream >> total_uptime;
    }

  return total_uptime ; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<long> LinuxParser::CpuUtilization() { 
  string key;
  string cpu_name;
  vector<long> cpu;
  long value;
  string line;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu_name;
    while(linestream >> value) {
      cpu.push_back(value);
    }
  }

  return cpu;

}

int LinuxParser::TotalProcesses() { 
    string key;
    int value;
    string line;

    //For each line, check if the first word == "procs_running"
    //    TRUE: return process number
    std::ifstream stream(kProcDirectory + kStatFilename);
    if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      // pull of the tokens from linestream:
      while (std::getline(stream, line)) {
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
          if (key == "processes") {
            return value;
          }
        }
      }
    }
    return value; 

}

int LinuxParser::RunningProcesses() { 
  string key;
  int value;
  string line;
  //TODO: refactor! is the second while even necessary?
  //For each line, check if the first word == "procs_running"
  //    TRUE: return process number
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // pull of the tokens from linestream:
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Command(int pid) { 
  string line;
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + "/" + kCmdlineFilename);

  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> command;

  }
  return command;
}

string LinuxParser::Ram(int pid) { 
  string key; 
  long value;
  string line;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
        if (key == "VmSize:") {
          return std::to_string(value/1000);
        }
    }
  }
  return "unknown-ram";
  }

string LinuxParser::Uid(int pid) { 
    string key; 
    string value = "";
    string line;

    std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if (stream.is_open()) {
      while (std::getline(stream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        linestream >> key >> value;
          if (key == "Uid:") {
            return value;
          }
      }
    }
    return value;
}

string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string user; 
  string value;
  string filler;  
  string line;

  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> filler >> value;
        if (value == uid) {
          return user;
        }
    }
  }
  return "unknown-user";
}


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }




// TODO: refactor key value parsing into template function?
// TODO: refactor RunningProcesses() and TotalProcesses()!
// TODO: how does stringstream work exactly?