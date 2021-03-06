#include "ncurses_display.h"
#include "system.h"

#include "linux_parser.h"
#include "processor.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
//    Processor processor;
//    processor.Utilization();
//    LinuxParser::Command(1);
//    LinuxParser::Uid(1);
//    LinuxParser::User(1);
//    LinuxParser::Ram(1);
//    LinuxParser::StatParser(1);
//    Process process = Process(1);
//    process.UpTime();
//    process.CpuUtilization();

}