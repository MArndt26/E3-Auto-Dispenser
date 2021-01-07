#ifndef E3_CORE_H
#define E3_CORE_H

#include "main.h"
#include <HX711.h>

#define ROWS 4
#define COLS 4

//constants
extern const int PAST_WEIGHT_BUF_SIZE;
extern const int SET_VAL_SIZE;

//enumerations
enum SCREEN
{
    HOME,
    PRESET,
    PROGRAM,
    RUN
};
extern SCREEN curScreen;

//keypad variables
extern byte rowPins[];
extern byte colPins[];

//weight variables
extern const int LOADCELL_DOUT_PIN;
extern const int LOADCELL_SCK_PIN;
extern HX711 scale;
struct weightFilter
{
    double total;
    int index;
    double past[];
};
extern double c_factor; //calibration factor
extern double weight;

//user variables
extern char setValStr[];
extern char curFNButton;
extern char prevFNButton;
extern char c;

#endif