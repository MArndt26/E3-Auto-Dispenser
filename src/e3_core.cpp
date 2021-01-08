#include "e3_core.h"

//constants
const int SET_VAL_SIZE = 4;

//enumerations
SCREEN curScreen = HOME;

const char FN1_Button = 'A';
const char FN2_Button = 'B';
const char FN3_Button = 'C';
const char TARE = 'D';
const char ENTER = '#';

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//weight variables
Scale scale = Scale();
double weight = 0.0;

//user variables
char setValStr[SET_VAL_SIZE + 1] = "-999";
char curFNButton = '\0';
char prevFNButton = '\0';
