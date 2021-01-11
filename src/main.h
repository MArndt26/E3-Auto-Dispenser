#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

//used to emulate pressing the foot pedal by pressing the Enter key
// #define HOME_KEYPAD_ENTER

//uncomment to use permanent storage (saves even when powered off)
#define PERMANENT_MEM

//uncomment to initialize permanent storage for new device (only do this once)
// #define INITIALIZE_PERMANENT_MEM

//4 digit passwords only!
#define CALIBRATION_PASSWORD "1234"

// uncomment to emulate lcd with serial terminal
#define VIRTUAL_SCREEN

//uncomment to emulate scale with random number generator
// #define VIRTUAL_SCALE

//uncomment to emulate error/success leds with serial terminal
// #define VIRTUAL_SIGNAL

//uncomment to emulate keypad matrix with computer keyboard input from serial terminal
// #define VIRTUAL_KEYBOARD

//uncomment to emulate digital with the serial terminal
// #define VIRTUAL_DIGITAL

#endif