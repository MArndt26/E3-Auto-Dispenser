#ifndef RUN_H
#define RUN_H

#include "run.h"
#include "state.h"
#include "scale.h"
#include "lcd.h"
#include "debug.h"
#include "controlFlow.h"
#include "buttons.h"

/*
 * RUN_PAGE: NOTE: get to this page by pressing # from Home Page when SET VAL has been entered
 * ------------------
 * |S:1234  C:1234.5|
 * | Press to Halt  |
 * ------------------
 */
void updateRunScreen()
{
    //first line
    lcd.setCursor(2, 0);
    lcd.print(setString);

    //second line
    lcd.setCursor(10, 0);
    lcd.print(weightString);
    lcd.print("      "); //clsear out rest of frame
}

void highPerformanceRun()
{
    for (;;)
    {
        getWeight();
        if (keypad.getKey())
        {
            return;
        }
        if (weightString.toInt() >= setString.toInt())
        {
            userSuccess();
            return;
        }

        updateRunScreen();
    }
}

#endif