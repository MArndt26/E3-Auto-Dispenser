#ifndef E3_LOADCELL_H
#define E3_LOADCELL_H

#include "Arduino.h"
#include <HX711.h>

class Scale
{
private:
    static const int LOADCELL_DOUT_PIN = 11;
    static const int LOADCELL_SCK_PIN = 10;
    static const int PAST_WEIGHT_BUF_SIZE = 15;
    double pastWeights[PAST_WEIGHT_BUF_SIZE];
    double total;
    int i;
    HX711 *_scale;

public:
    double c_factor;
    int setVal;
    double weight;

    Scale();

    ~Scale();

    void getWeight();

    void tare();
};

#endif