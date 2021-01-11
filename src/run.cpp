#include "run.h"
#include "e3_core.h"

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

    int whole;
    unsigned int frac;

    floatToString(e3_scale.weight, &whole, &frac);
    snprintf(line, 17, "S:%4d C:%4d.%1u", e3_scale.setVal, whole, frac);

    screen.home();
    screen.print(line);

    screen.setCursor(0, 1);
    screen.print(" Press to Halt");
}

void run()
{
    screen.clear();
    screen.home();

    // digital.relaysOn(); //ensure that all relays turn on

    for (;;)
    {
        e3_scale.updateWeight(memory.c_factor);

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