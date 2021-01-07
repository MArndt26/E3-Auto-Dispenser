#include "scale.h"

const int PAST_WEIGHT_BUF_SIZE = 15;

HX711 scale;
double weight;
double pastWeights[PAST_WEIGHT_BUF_SIZE];
double c_factor = 464.5f;
double total = 0;
int readIndex = 0;

void tareScale()
{
    //set readings array to all zeros
    for (int i = 0; i < PAST_WEIGHT_BUF_SIZE; i++)
    {
        pastWeights[i] = 0.0f;
    }
    total = 0.0; //reset total
    scale.tare(5);
}

void scaleInit()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(c_factor); //Adjust to this calibration factor
    scale.tare(10);
}

void getWeight()
{
    // subtract the last reading:
    total = total - pastWeights[readIndex];
    // read from the sensor:
    pastWeights[readIndex] = (double)scale.get_value() / c_factor;

    // add the reading to the total:
    total = total + pastWeights[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= PAST_WEIGHT_BUF_SIZE)
    {
        // ...wrap around to the beginning:
        readIndex = 0;
    }

    // calculate the average:
    weight = total / (double)PAST_WEIGHT_BUF_SIZE;
}