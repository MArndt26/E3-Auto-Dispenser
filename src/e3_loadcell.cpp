#include "e3_loadcell.h"
#include <HX711.h>

const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 10;
const int PAST_WEIGHT_BUF_SIZE = 15;

E3_SCALE e3_scale;
HX711 _scale;

double pastWeights[PAST_WEIGHT_BUF_SIZE] = {0.0};
double total = 0.0;
int i = 0;

void scaleInit()
{
    e3_scale.c_factor = 464.5f;
    e3_scale.setVal = -999;
    e3_scale.weight = 0.0;

    _scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    _scale.set_scale(e3_scale.c_factor); //Adjust to this calibration factor
    _scale.tare(10);
}

void getWeight()
{
    // subtract the last reading:
    total = total - pastWeights[i];
    // read from the sensor:
    pastWeights[i] = (double)_scale.get_value() / e3_scale.c_factor;

    // add the reading to the total:
    total = total + pastWeights[i];
    // advance to the next position in the array:
    i++;

    // if we're at the end of the array...
    if (i >= PAST_WEIGHT_BUF_SIZE)
    {
        // ...wrap around to the beginning:
        i = 0;
    }

    // calculate the average:
    e3_scale.weight = total / (double)PAST_WEIGHT_BUF_SIZE;
}

void tare()
{
    //set readings array to all zeros
    for (int i = 0; i < PAST_WEIGHT_BUF_SIZE; i++)
    {
        pastWeights[i] = 0.0f;
    }
    total = 0.0; //reset total
    e3_scale.weight = 0.0;
    _scale.tare(5);
}

// Scale::Scale()
// {
//     c_factor = 464.5f;
//     setVal = -999;
//     weight = 0.0;
//     pastWeights[PAST_WEIGHT_BUF_SIZE] = {0.0};
//     total = 0.0;
//     i = 0;

//     _scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
//     _scale.set_scale(c_factor); //Adjust to this calibration factor
//     _scale.tare(10);
// }

// void Scale::getWeight()
// {
//     // subtract the last reading:
//     total = total - pastWeights[i];
//     // read from the sensor:
//     pastWeights[i] = (double)_scale.get_value() / c_factor;

//     // add the reading to the total:
//     total = total + pastWeights[i];
//     // advance to the next position in the array:
//     i++;

//     // if we're at the end of the array...
//     if (i >= PAST_WEIGHT_BUF_SIZE)
//     {
//         // ...wrap around to the beginning:
//         i = 0;
//     }

//     // calculate the average:
//     weight = total / (double)PAST_WEIGHT_BUF_SIZE;
// }

// void Scale::tare()
// {
//     //set readings array to all zeros
//     for (int i = 0; i < PAST_WEIGHT_BUF_SIZE; i++)
//     {
//         pastWeights[i] = 0.0f;
//     }
//     total = 0.0; //reset total
//     weight = 0.0;
//     _scale.tare(5);
// }