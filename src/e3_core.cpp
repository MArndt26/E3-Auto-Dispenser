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

//user variables
char setValStr[SET_VAL_SIZE + 1] = "";
char curFNButton = '\0';
char prevFNButton = '\0';

//permenant memory variables
Memory memory = Memory();

//scale variables
const uint8_t LOADCELL_DOUT_PIN = 11;
const uint8_t LOADCELL_SCK_PIN = 10;
Scale e3_scale = Scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

//lcd object
e3_lcd screen = e3_lcd(0x27, 16, 2);

//led signaling object
const int errorPin = 13;
const int successPin = 12;
Signal signal = Signal(errorPin, successPin);

// relay pins
const uint8_t PUMP_CTRL_PIN = A3;
const uint8_t IO_1_PIN = A2;
const uint8_t FOOT_SWITCH_PIN = A1;
E3_Digital digital = E3_Digital(PUMP_CTRL_PIN, IO_1_PIN, FOOT_SWITCH_PIN);