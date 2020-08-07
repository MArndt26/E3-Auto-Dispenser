//HUSH used to remove all serial other than serial screen emulation
#define HUSH 0
#define HUSH_ERRORS 0
#define HUSH_SUCCESS 0
#define NO_HOME_KEYPAD_ENTER 1

#define SERIAL_DEBUG 0

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
#include "digital.h"
#include "debug.h"

#include "controlFlow.h"

void setup()
{
    masterInit();

    #if HUSH
    Serial.println("Setup Complete");
    debugVars();
    #endif

    updateScreenImmediate();
}

void loop()
{
    handleInput(); //reads in and handles input

    #if HUSH
    debugVars();
    #endif

    switch (curState)
    {
    case HOME_STATE:
        relaysOff();
        updateScreen();
        break;
    case PRESET_STATE:
        relaysOff();
        break;
    case PROGRAM_STATE:
        relaysOff();
        break;
    case RUN_STATE:
        relaysOn();
        if (weightString.toInt() >= setString.toInt())
        {
            doStateChange();
            userSuccess();
            #if HUSH_SUCCESS
            Serial.println("Success: Finished Filling Cup");
            #endif
        }
        if (first)
        {
            if (millis() - time_now > frontDelay)
            {
                offset++;
                first = false;
                time_now = millis();
                updateScreenImmediate();
            }
        }
        else if (millis() - time_now > period)
        {
            if (offset == 0)
            {
                first = true;
            }
            else
            {
                offset++;
            }
            time_now = millis();
            updateScreenImmediate();
        }
        break;
    }
}