#ifndef DEBUG_H
#define DEBUG_H

#include "main.h"

/*---------------DEBUG VARS-----------------*/
#define errorPin 13
#define successPin 12

/*---------------DEBUG FUNCTIONS------------*/
void debugInit();

void userError();

void userSuccess();

#if HUSH
void debugVars();
#endif

#endif //DEBUG_H