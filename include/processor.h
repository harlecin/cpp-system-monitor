#pragma once

class Processor {
 public:
  float Utilization();  

 private:
    long PrevTotal = 0;
    long PrevIdle = 0;
};


//TODO: very first call not correct: Should I fix this?