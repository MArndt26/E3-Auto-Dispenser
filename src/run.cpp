#include "run.h"
#include "e3_core.h"
#include "e3_loadcell.h"

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
    char line[17];
    // char buf[8];
    // dtostrf(e3_scale.weight, 8, 1, buf);
    snprintf(line, 17, "S:%4d C:%6.1f", e3_scale.setVal, e3_scale.weight);
    screen.lcd.print(line);

    screen.lcd.setCursor(0, 1);
    screen.lcd.print(" Press to Halt");
}

void run()
{
    digital.relaysOn(); //ensure that all relays turn on
    screen.lcd.clear();

    e3_scale.setVal = memory.fn1;
    for (;;)
    {
        e3_scale.getWeight();

        if (keypad.getKey())
        {
            signal.error();
            return;
        }
        if (e3_scale.weight >= e3_scale.setVal)
        {
            signal.success();
            return;
        }

        updateRunScreen();
    }
}