#include "scale.h"

/*----------------SCALE VARS----------------*/
String weightString = "";

//DATA SMOOTHING VARS
const int numReadings = 10; //used for running average

double readings[numReadings]; // the readings from the analog input
int readIndex = 0;            // the index of the current reading
double total = 0.0f;          // the running total
double average = 0.0f;        // the average

HX711 scale;

/*----------------SCALE FUNCTIONS----------------*/
void tareScale()
{
    //set readings array to all zeros
    for (int thisReading = 0; thisReading < numReadings; thisReading++)
    {
        readings[thisReading] = 0.0f;
    }
    total = 0.0; //reset total
    scale.tare(5);
}

void scaleInit()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.set_scale(calibration_factor); //Adjust to this calibration factor
    tareScale();
#if HUSH
    Serial.println("Scale Initialized");
#endif
}

void getWeight()
{
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = (double)scale.get_value() / calibration_factor;

    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings)
    {
        // ...wrap around to the beginning:
        readIndex = 0;
    }

    // calculate the average:
    average = total / (double)numReadings;

    weightString = String(average, 1);
}
