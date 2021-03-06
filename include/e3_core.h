#ifndef E3_CORE_H
#define E3_CORE_H

#include "main.h"
#include <Keypad.h>
#include "e3_memory.h"
#include "e3_loadcell.h"
#include "e3_lcd.h"
#include "e3_signal.h"
#include "e3_digital.h"
#include "e3_serial.h"

//screen object
#ifdef VIRTUAL_SCREEN
extern E3_Serial screen; // = E3_Serial();
#else
//lcd object
extern E3_LCD screen; // = E3_LCD(0x27, 16, 2);
#endif

//enumerations
enum SCREENS
{
    HOME,
    PRESET,
    PROGRAM,
    RUN,
    CALIBRATE
};
extern SCREENS curScreen;

//weight variables
extern Scale e3_scale;

/*--------------KEYPAD VARS------------------*/
extern const char FN1_Button;
extern const char FN2_Button;
extern const char FN3_Button;
extern const char TARE;
extern const char ENTER;
extern const char CALIBRATE_BUTTON;

#ifdef VIRTUAL_KEYBOARD
class VirtualKeypad
{
public:
    char getKey();
    void setDebounceTime(int t);
};

extern VirtualKeypad keypad;
#else
extern Keypad keypad;
#endif

//led signaling object
extern Signal signal;

//permenant memory variables
extern E3_Memory memory;

//digital object for relays and foot switch
extern E3_Digital digital;

bool append(char *str, int maxLen, char c);

//constants
extern const int SET_VAL_SIZE;

void floatToString(double input, int *whole, unsigned int *frac);

//user variables
extern char setValStr[];
extern char curFNButton;
extern char prevFNButton;

#endif