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
    whole = 10;
    frac = 5;
    // floatToString(e3_scale.weight, &whole, &frac);
    snprintf(line, 17, "S:%4d C:%4d.%1u", 1234, whole, frac);

    screen.home();

    Serial.write(line);
    Serial.println("here");
    delay(1000);

    screen.print(line);

    screen.setCursor(0, 1);
    screen.print(" Press to Halt");

    delay(500);
}

void run()
{
    screen.clear();
    screen.home();

    // digital.relaysOn(); //ensure that all relays turn on

    // e3_scale.setSetVal(memory.getFN1());

    for (;;)
    {
        // e3_scale.updateWeight();

        // if (keypad.getKey())
        // {
        //     signal.error();
        //     return;
        // }
        // if (e3_scale.weight >= e3_scale.setVal)
        // {
        //     signal.success();
        //     return;
        // }

        updateRunScreen();
    }
}