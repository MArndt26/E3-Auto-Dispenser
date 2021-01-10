#ifndef E3_LOADCELL_H
#define E3_LOADCELL_H

#include "main.h"
#include <HX711.h>

class Scale
{
private:
    static const int PAST_WEIGHT_BUF_SIZE = 15;
    double pastWeights[PAST_WEIGHT_BUF_SIZE];
    double total;
    int i;
    HX711 _scale;

public:
    double c_factor;
    int setVal;
    double weight;

    Scale(const int dout, const int sck);

    void getWeight();

    void tare();
};

#endif