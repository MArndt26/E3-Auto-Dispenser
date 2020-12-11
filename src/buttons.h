#ifndef BUTTONS_H
#define BUTTONS_H

#include "main.h"
#include <Keypad.h>

/*--------------KEYPAD VARS------------------*/
#define FN1_Button  'A'
#define FN2_Button  'B'
#define FN3_Button  'C'
#define TARE        'D'
#define ENTER       '#'

#define ROWS 4
#define COLS 4

void keypadInit();

int getKeyPressed();

void clearFN_Buttons();

extern char c; //holds value read in by keypad

extern char prev_FN_Button;
extern char cur_FN_Button;


extern char hexaKeys[ROWS][COLS];

extern byte rowPins[ROWS];
extern byte colPins[COLS];

// //main keypad object
extern Keypad keypad;

#endif 