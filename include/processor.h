#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  

 private:
    long PrevTotal = 0;
    long PrevIdle = 0;
};

#endif

//TODO: very first call not correct: Should I fix this?