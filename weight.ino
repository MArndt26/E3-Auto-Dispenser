#include <EEPROM.h>
#include <Keypad.h>
#include "LiquidCrystal_I2C.h"
#include "HX711.h"
#include "declarations.h"
#include "functions.h"

void setup()
{
    userFunctionsInit();

    Serial.println("Program Start"); //needs to wait for Serial to be initialized

    scaleInit();

    //read in from eeprom the previous setVal
    EEPROM_ReadAll();

    //initialize lcd object
    lcdInit();

    debugVars();
    Serial.println("Setup Complete");
}

void loop()
{
    // char c = keypad.getKey(); //returns the key that is pressed or ##### if no key is pressed
    c = '\0';
    while (Serial.available() > 0)
    {
        c = Serial.read();
        Serial.print("echo: ");
        Serial.println(c);
    }

    switch (curState)
    {
    case PROGRAM_STATE:
        relaysOff();

        if (c >= '0' && c <= '9') //check if key pressed is in the range [0, 9]
        {
            if (curString.length() < DISP_SET_STR_MAX_LEN) //check if you are trying to type off the screen
            {
                appendChar();
            }
            else
            {
                userError("in c=[0, 9]");
            }
        }
        else if (c == '.')
        {
            if (curString == "")
            {
                userError("Cannot Start with dp");
            }
            else if (curString[curString.length() - 1] == '.')
            {
                userError("Cannot have back-to-back dps");
            }
            else if (curString.length() == DISP_SET_STR_MAX_LEN)
            {
                userError("Cannot add a dp at end of string");
            }
            else if (curString.indexOf(".") != -1)
            {
                userError("Cannot have two dps");
            }
            else
            {
                appendChar();
            }
        }
        else if (c == '#') //enter key has been pressed
        {
            if (curString == "") //no user input
            {
                userError("Tried to Save Empty String");
            }
            else
            {
                saveScreen();

                printLCD();

                userSuccess();
            }
        }
        else if (c == CLEAR)
        {
            clearDisplay();
            printLCD();
        }
        else if (c == START_STOP)
        {
            curState = RUN_STATE;
        }
        else if (c >= 'A' && c <= 'D')
        {
            debugVars();
            //work with function buttons
        }
        break;
    case RUN_STATE:
        relaysOn();
        if (c == START_STOP)
        {
            curState = PROGRAM_STATE;
            userSuccess("Halted Run State");
            break;
        }
        // if (scale.get_units() >= setString.toFloat())
        if (c == '$') //for debugging
        {
            curState = PROGRAM_STATE;
            break;
        }
        break;
    }
}