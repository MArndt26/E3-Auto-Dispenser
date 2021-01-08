#include "main.h"

#if CALIBRATE
#include "calibrate.h"
void setup()
{
    setup_calibrate_scale();
}
void loop()
{
    calibrate_scale();
}
#else

#include "e3_core.h"
// #include <Keypad.h>
// #include <Wire.h>
// #include "LiquidCrystal_I2C.h"
// #include "time.h"
// #include "HX711.h"
// #include "state.h"
#include "lcd.h"
// #include "EE_MEM.h"
// #include "digital.h"
#include "debug.h"
#include "run.h"
#include "home.h"

// #include "controlFlow.h"

void setup()
{
    debugInit();

    lcdInit();

    scaleInit();

    // masterInit();

#if HUSH
    Serial.println("Setup Complete");
    debugVars();
#endif

    // updateScreenImmediate();
}

void loop()
{
    switch (curScreen)
    {
    case HOME:
        home();
        break;
    case PRESET:
        // relaysOff();
        break;
    case PROGRAM:
        // relaysOff();
        break;
    case RUN:
        run();
        curScreen = HOME;
        break;
    }
}
#endif