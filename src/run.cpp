#include "run.h"
#include "e3_core.h"
#include "lcd.h"
#include "digital.h"

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
    char buf[8];
    dtostrf(e3_scale.weight, 8, 1, buf);
    lcd.setCursor(8, 0);
    lcd.print(buf);
}

void run()
{
    relaysOn(); //ensure that all relays turn on
    lcd.clear();

    e3_scale.setVal = memory.fn1;
    for (;;)
    {
        getWeight();

        if (keypad.getKey())
        {
            userError();
            return;
        }
        if (e3_scale.weight >= e3_scale.setVal)
        {
            userSuccess();
            return;
        }

        updateRunScreen();
    }
}