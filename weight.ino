#include <EEPROM.h>
#include <Keypad.h>
#include "LiquidCrystal_I2C.h"
#include "state.h"
#include "keypad.h"
#include "lcd.h"
#include "HX711.h"
#include "EE_MEM.h"
#include "scale.h"
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

    if (c != '\0')
    {
        if (c >= FN1 && c <= FN3) //function button pressed
        {
            cur_FN_Button = c;
            doStateChange();
        }
        else if (c == '#') //enter button pressed
        {
            doStateChange();
        }
        else if (checkValidInput()) //check if input is valid for remaining characters
        {
            appendChar();
        }
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
        if (c != '\0') //check if key is pressed to interupt run cycle
        {
            doStateChange();
        }
        break;
    }
}