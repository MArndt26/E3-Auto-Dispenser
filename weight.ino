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

    setString = "1";
    c = ENTER;
    doStateChange();

    updateScreen();
    delay(500);
    for (int i = 0; i < PROGRAM_DISP_SET_STR_MAX_LEN; i++)
    {
        char c = '1' + i;
        setString += c;
        updateScreen();

        delay(500);
    }
}

void loop()
{
    getInputs();

    if (c != '\0')
    {
        if (c >= FN1_Button && c <= FN3_Button) //function button pressed
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