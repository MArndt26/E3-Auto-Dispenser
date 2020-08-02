//HUSH used to remove all serial other than serial screen emulation
#define HUSH 0

#include <EEPROM.h>
#include <Keypad.h>
#include "LiquidCrystal_I2C.h"
#include "HX711.h"
#include "state.h"
#include "keypad.h"
#include "scale.h"
#include "lcd.h"
#include "EE_MEM.h"
#include "debug.h"

#include "controlFlow.h"

void setup()
{
    masterInit();

#if HUSH
    Serial.println("Setup Complete");
#endif

    debugVars();

    updateScreen();
}

void loop()
{
    handleInput();

    switch (curState)
    {
    case HOME_STATE:
        break;
    case PRESET_STATE:
        break;
    case PROGRAM_STATE:
        break;
    case RUN_STATE:
        break;
    }
}