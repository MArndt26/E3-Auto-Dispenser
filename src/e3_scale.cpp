#include "e3_scale.h"
#include "e3_core.h"

Scale::Scale()
{
    _scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    _scale.set_scale(c_factor); //Adjust to this calibration factor
    _scale.tare(10);
}

double Scale::getWeight()
{
    // subtract the last reading:
    total = total - pastWeights[i];
    // read from the sensor:
    pastWeights[i] = (double)_scale.get_value() / c_factor;

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
    return total / (double)PAST_WEIGHT_BUF_SIZE;
}

void Scale::tare()
{
    //set readings array to all zeros
    for (int i = 0; i < PAST_WEIGHT_BUF_SIZE; i++)
    {
        pastWeights[i] = 0.0f;
    }
    total = 0.0; //reset total
    _scale.tare(5);
}