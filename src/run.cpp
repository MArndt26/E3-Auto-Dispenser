#ifndef RUN_H
#define RUN_H

#include "run.h"
#include "state.h"
#include "scale.h"
#include "lcd.h"
#include "debug.h"
#include "controlFlow.h"
#include "buttons.h"

void highPerformanceRun()
{
    boolean first = true;
    extern unsigned int period;
    extern unsigned int frontDelay;
    unsigned long time_now = millis();
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

        if (first)
        {
            offset = 0;
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
    }
}

#endif