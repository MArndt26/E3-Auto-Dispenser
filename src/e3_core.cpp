#include "e3_core.h"

//constants
const int SET_VAL_SIZE = 4;

//enumerations
SCREEN curScreen = HOME;

//weight variables
const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 10;

//user variables
char setValStr[SET_VAL_SIZE + 1] = {};
char curFNButton = '\0';
char prevFNButton = '\0';
char c = '\0';
