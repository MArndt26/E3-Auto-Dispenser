#include <EEPROM.h>
#include <Keypad.h>
#include "LiquidCrystal_I2C.h"
#include "HX711.h"
#include "state.h"
#include "scale.h"
#include "keypad.h"
#include "lcd.h"
#include "debug.h"

#include "controlFlow.h"

void setup()
{
    masterInit();

    Serial.println("Setup Complete");

    updateScreen();
}

void loop()
{
    getInputs();

    if (c >= FN1 && c <= FN3)
    {
        cur_FN_Button = c;
        doStateChange();
    }
    else if (c == '#')
    {
        doStateChange();
    }

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