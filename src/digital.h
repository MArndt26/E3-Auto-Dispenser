#ifndef DIGITAL_H
#define DIGITAL_H

#include "main.h"

/*---------------DIGITAL Vars-------------------*/
#define PUMP_CTRL_PIN       A3
#define IO_1_PIN            A2
#define FOOT_SWITCH_PIN     A1

void relaysOn();

void relaysOff();

int readFootSwitch();

void relayInit();

#endif