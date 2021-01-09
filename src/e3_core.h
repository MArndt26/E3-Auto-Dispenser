#ifndef E3_CORE_H
#define E3_CORE_H

#include "main.h"
#include <Keypad.h>
#include "Memory.h"
#include "e3_loadcell.h"
#include "e3_lcd.h"
#include "e3_signal.h"
#include "e3_digital.h"

#define ROWS 4
#define COLS 4

bool append(char *str, int maxLen, char c);

//constants
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

/*--------------KEYPAD VARS------------------*/
extern const char FN1_Button;
extern const char FN2_Button;
extern const char FN3_Button;
extern const char TARE;
extern const char ENTER;

extern Keypad keypad;

//weight variables
extern Scale e3_scale;

//user variables
extern char setValStr[];
extern char curFNButton;
extern char prevFNButton;

//permenant memory variables
extern Memory memory;

//lcd object
extern e3_lcd screen;

//led signaling object
extern Signal signal;

//digital object for relays and foot switch
extern E3_Digital digital;

#endif