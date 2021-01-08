#ifndef E3_SCALE_H
#define E3_SCALE_H

#include "Arduino.h"
#include <HX711.h>

class Scale : public HX711
{
private:
    static const int LOADCELL_DOUT_PIN = 11;
    static const int LOADCELL_SCK_PIN = 10;
    static const int PAST_WEIGHT_BUF_SIZE = 15;
    double pastWeights[PAST_WEIGHT_BUF_SIZE];
    double total = 0;
    int i = 0;
    HX711 _scale;

public:
    double c_factor;
    int setVal;
    double weight;

    Scale();

    void getWeight();

    void tare();
};

#endif