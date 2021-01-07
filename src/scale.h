#ifndef SCALE_H
#define SCALE_H

#include "main.h"

#if CALIBRATE
#include <HX711.h>
extern HX711 scale;
#endif

/*----------------SCALE VARS----------------*/
extern String weightString;
extern double weight;

#define LOADCELL_DOUT_PIN 11
#define LOADCELL_SCK_PIN 10

//DATA SMOOTHING VARS
//used for running average
#define numReadings 10

extern double readings[numReadings]; // the readings from the analog input
extern int readIndex;                // the index of the current reading
extern double total;                 // the running total
extern double average;               // the average

#if CALIBRATE
extern float calibration_factor;
#else
extern const float calibration_factor;
#endif

/*----------------SCALE FUNCTIONS----------------*/
void tareScale();

void scaleInit();

void getWeight();

#endif