#ifndef MEMORY_H
#define MEMORY_H

#include "Arduino.h"

#define PERMANENT_MEM 1

class Memory
{
private:
    static const int fn1_addr = 0 * sizeof(int);
    static const int fn2_addr = 1 * sizeof(int);
    static const int fn3_addr = 2 * sizeof(int);

    static const int MAX_VAL = 9999;

public:
    int fn1;
    int fn2;
    int fn3;

    Memory();

    void read();

    void write();

    void write(int i);
};

#endif