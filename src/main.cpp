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
#include "run.h"
#include "home.h"

void setup()
{
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