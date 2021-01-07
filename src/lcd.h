#ifndef LCD_H
#define LCD_H

#include "main.h"

#include <LiquidCrystal_I2C.h>
extern LiquidCrystal_I2C lcd;

/*--------------LDC VARS----------------*/
//Resource: https://gitlab.com/tandembyte/LCD_I2C

//Custom Characters
#define LOCKED 1
#define UNLOCKED 0

//SCREEN
#define SCREEN_X 16

//HOME SCREEN
#define WEIGHT_LINE_NUMBER 0
#define SET_LINE_NUMBER 1

#define SET_CURSOR_START 4
#define MASS_CURSOR_START 5

#define SET_MSG "SetVal:"
#define WEIGHT_MSG "WEIGHT:"

//16 - 1 - 4; //Note: changing this can corrupt the data stored on eeprom
#define DISP_SET_STR_MAX_LEN 7
//16 - 1 - 5
#define DISP_WEIGHT_STR_MAX_LEN 8

//SHIFTING VARS
extern unsigned short offset;

//PRESET SCREEN
#define PRESET_MSG "PREST:"
#define PRESET_ENTER_MSG " PRESS # to SET "

#define PRESET_DISP_SET_STR_MAX_LEN 9

//PROGRAM SCREEN
#define PROGRAM_MSG "PROGR:"
#define PROGRAM_ENTER_MSG "PRESS # to PROGR"

#define PROGRAM_DISP_SET_STR_MAX_LEN 9

//RUN SCREEN
#define RUN_WARN_MSG "g [PRESS ANY KEY TO STOP]"

extern String curString; //value user is currently typing in
extern String setString; //set value saved to eeprom

extern String fn1String; //fn1 value saved to eeprom
extern String fn2String; //fn2 value saved to eeprom
extern String fn3String; //fn3 value saved to eeprom

//TARE SCREEN
// #define TARE_MSG "------TARE------"
// #define BLANK_LINE "                "

/*--------------LCD FUNCTIONS-----------------*/
String getFN_String();

void serialSetCursor(int row, int col);

void lcdInit();

// void homeScreen();

// void presetScreen();

// void programScreen();

// void runScreen();

// void tareScreen();

// void updateScreenImmediate();

// void appendChar();

#endif