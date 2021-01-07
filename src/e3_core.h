#ifndef E3_CORE_H
#define E3_CORE_H

#include "main.h"
#include <HX711.h>

#define FN1_Button 'A'
#define FN2_Button 'B'
#define FN3_Button 'C'
#define TARE 'D'
#define ENTER '#'

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