#include "ncurses_display.h"
#include "system.h"

#include "linux_parser.h"
#include "processor.h"

int main() {
  System system;
  NCursesDisplay::Display(system);
}