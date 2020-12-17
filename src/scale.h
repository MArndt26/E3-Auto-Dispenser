#ifndef SCALE_H
#define SCALE_H

#include "main.h"

/*----------------SCALE VARS----------------*/
extern String weightString;

#define LOADCELL_DOUT_PIN 11
#define LOADCELL_SCK_PIN 10

//DATA SMOOTHING VARS
//used for running average
#define numReadings 10

extern double readings[numReadings]; // the readings from the analog input
extern int readIndex;                // the index of the current reading
extern double total;                 // the running total
extern double average;               // the average

#define calibration_factor 464.5f

/*----------------SCALE FUNCTIONS----------------*/
void tareScale();

void scaleInit();

void getWeight();

#endif