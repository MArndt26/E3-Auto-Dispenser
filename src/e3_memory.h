#ifndef MEMORY_H
#define MEMORY_H

#include "main.h"

class E3_Memory
{
private:
    static const int fn1_addr = 0 * sizeof(int);
    static const int fn2_addr = 1 * sizeof(int);
    static const int fn3_addr = 2 * sizeof(int);
    static const int c_fact_addr = 3 * sizeof(int);

    static const int MAX_VAL = 9999;

public:
    double c_factor;
    int fn1;
    int fn2;
    int fn3;

    E3_Memory();

    void readAll();

    void writeFN(int i, int val);

    void writeCF();

    int getFN(int i);
};

#endif