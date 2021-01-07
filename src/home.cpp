#ifndef HOME_H
#define HOME_H

#include "home.h"
#include "controlFlow.h"
#include "scale.h"
#include "lcd.h"
#include "debug.h"
#include "buttons.h"
#include "state.h"

// same as above without clearing screen
void updateHomeScreen()
{
    //first line
    char line[17];
    char buf[8];
    weightString.toCharArray(buf, 8);
    snprintf(line, 17, "WEIGHT:%-8sg", buf);
    lcd.home();
    lcd.print(line);

    //second line
    lcd.setCursor(0, 1);
    if (curString == "")
    {
        setString.toCharArray(buf, 8);
        lcd.write(LOCKED);
    }
    else
    {
        curString.toCharArray(buf, 8);
        lcd.write(UNLOCKED);
    }
    snprintf(line, 17, "SetVal:%-7sg", buf);
    lcd.print(line);
}

void highPerformanceHomeScreen()
{
    for (;;)
    {
        getWeight(); //gets smoothed weight and assigns to weight string

        getKeyPressed(); //gets key pressed and writes to global var c

        handleDigital(); //overrides key pressed if foot switch is pressed

        if (c != '\0') //check if input exists
        {
            if (c == TARE) //tare only works from home screen
            {
                tareScreen();
                tareScale();
                lcd.home();
                homeScreen();
            }
            else
            {
                handleKeypad(true);
            }
            break;
            c = '\0'; //consume character
        }

        if (curState != HOME_STATE)
        {
            return;
        }

        // lcd.home();
        // homeScreen();
        updateHomeScreen();
    }
}

#endif