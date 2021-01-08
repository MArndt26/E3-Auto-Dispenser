#include "e3_core.h"

//constants
const int SET_VAL_SIZE = 4;

bool append(char *str, int maxLen, char c)
{
    for (int i = 0; i < maxLen; i++)
    {
        if (!str[i])
        {
            str[i] = c;
            str[i + 1] = '\0';
            return true;
        }
    }
    return false;
}

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

//user variables
char setValStr[SET_VAL_SIZE + 1] = "";
char curFNButton = '\0';
char prevFNButton = '\0';
