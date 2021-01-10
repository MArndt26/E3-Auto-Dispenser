#ifndef MEMORY_H
#define MEMORY_H

#include "main.h"

class E3_Memory
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

    E3_Memory();

    void read();

    void write();

    void write(int i);
};

#endif