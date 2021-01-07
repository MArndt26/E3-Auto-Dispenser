#ifndef CONTROL_FLOW_H
#define CONTROL_FLOW_H

#include "main.h"

/*----------------CONTROL FLOW VARS---------------*/
#define NO_INPUT 0
#define INPUT_IS_FN 1
#define INPUT_IS_DIGIT 2
#define INPUT_IS_ENTER 3

void masterInit();

void doStateChange();

boolean handleFN();

void handleKeypad(boolean keypadAllowed);

void handleDigital();

void handleInput();

void updateScreen();

#endif