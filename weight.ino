//HUSH used to remove all serial other than serial screen emulation
#define HUSH 0

#include <EEPROM.h>
#include <Keypad.h>
#include <Wire.h>
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
    handleInput(); //reads in and handles input

    switch (curState)
    {
    case HOME_STATE:
        break;
    case PRESET_STATE:
        break;
    case PROGRAM_STATE:
        break;
    case RUN_STATE:

        if (first)
        {
            if (millis() - time_now > frontDelay)
            {
                offset++;
                first = false;
                time_now = millis();
                updateScreen();
            }
        }
        else if (millis() - time_now > period)
        {
            Serial.println(offset);
            if (offset == 0)
            {
                first = true;
            }
            else
            {
                offset++;
            }
            time_now = millis();
            updateScreen();
        }
        break;
    }
}