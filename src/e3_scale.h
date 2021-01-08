#ifndef E3_SCALE_H
#define E3_SCALE_H

#include "Arduino.h"
#include <HX711.h>

struct E3_SCALE
{
    double c_factor;
    double weight;
    int setVal;
};

extern E3_SCALE e3_scale;

void scaleInit();

void getWeight();

void tare();

// class Scale
// {
// private:
//     static const int LOADCELL_DOUT_PIN = 11;
//     static const int LOADCELL_SCK_PIN = 10;
//     static const int PAST_WEIGHT_BUF_SIZE = 15;
//     double pastWeights[PAST_WEIGHT_BUF_SIZE];
//     double total;
//     int i;
//     HX711 _scale;

// public:
//     double c_factor;
//     int setVal;
//     double weight;

//     Scale();

//     void getWeight();

//     void tare();
// };

#endif