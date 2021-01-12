#include "calibrate.h"
#include "e3_core.h"
#include "common.h"

const char PASSWORD[5] = CALIBRATION_PASSWORD;
int LOCKED = 1;

#define CHARMAP_SIZE 8
const struct
{
    char key[CHARMAP_SIZE];
    float val[CHARMAP_SIZE];
} charMap = {
    .key = {'A', '3', '2', '1', 'B', '6', '5', '4'},
    .val = {0.1, 1, 10, 100, -0.1, -1, -10, -100}};

void saveCFScreen()
{
    screen.clear();

    char line[17];
    int whole;
    unsigned int frac;

    //first line
    floatToString(memory.c_factor, &whole, &frac);
    snprintf(line, 17, "Saved: %4d.%1d", whole, frac);

    screen.home();
    screen.print(line);
}

void updateCalibrateScreen()
{
    char line[17];

    int whole;
    unsigned int frac;

    //first line
    floatToString(e3_scale.weight, &whole, &frac);
    snprintf(line, 17, "WEIGHT:%6d.%1ug", whole, frac);

    screen.home();
    screen.print(line);

    //second line
    floatToString(memory.c_factor, &whole, &frac);
    snprintf(line, 17, "CALIBR F:%5d.%1d", whole, frac);

    screen.setCursor(0, 1);
    screen.print(line);
}

void updateCalibrateLockScreen()
{
    screen.setCursor(1, 0);
    screen.print("Enter Password");

    char line[17];

    snprintf(line, 17, ">%-4s", setValStr);
    screen.setCursor(0, 1);
    screen.print(line);
}

void incorrectPasswordScreen()
{
    screen.clear();
    screen.home();
    screen.print("Invalid Password");
}

void handleNumeric_lock(char c)
{
    bool appended = append(setValStr, SET_VAL_SIZE, c);

    if (!appended)
    {
        // handle overflow
        setValStr[0] = '\0'; //clear string
        signal.error();
        return;
    }
}

void handleEnter_lock()
{
    LOCKED = 0; //unlock
    for (int i = 0; i < SET_VAL_SIZE; i++)
    {
        char temp = setValStr[i];
        setValStr[i] = '\0'; //clear string as you interate through it
        if (temp != PASSWORD[i])
        {
            LOCKED = 1; //lock
            return;
        }
    }
}

void calibrate_lock()
{
    screen.clear();

    for (;;)
    {
        char c = keypad.getKey();

#ifdef VIRTUAL_DIGITAL
        if (c == 'f')
#else
        if (digital.checkFS())
#endif
        {
            signal.error();
        }
        else if (c != '\0')
        {
            if (c >= '0' && c <= '9')
            {
                handleNumeric_lock(c);
            }
            else if (c == ENTER)
            {
                handleEnter_lock();
                if (LOCKED)
                {
                    incorrectPasswordScreen();
                    delay(1000);
                }
                return;
            }
            else if (c == CALIBRATE_BUTTON)
            {
                setValStr[0] = '\0';
                signal.error();
                return;
            }
            else
            {
                signal.error();
            }
        }

        updateCalibrateLockScreen();
    }
}

void calibrate()
{
    digital.relaysOff();
    calibrate_lock();

    double tempC_Factor = memory.c_factor;

    if (LOCKED)
    {
        curScreen = HOME;
        return;
    }

    screen.clear();

    for (;;)
    {
        e3_scale.updateWeight(memory.c_factor);

        // using keypad to update factor
        char c = keypad.getKey();

#ifdef VIRTUAL_DIGITAL
        if (c == 'f')
#else
        if (digital.checkFS())
#endif
        {
            signal.error();
        }
        else if (c != '\0')
        {
            if (c == TARE)
            {
                tareScreen();
                e3_scale.tare();
                delay(200);
                updateCalibrateScreen();
            }
            else if (c == ENTER)
            {
                memory.writeCF();
                saveCFScreen();
                curScreen = HOME;
                signal.success();
                delay(1000);
            }
            else if (c == CALIBRATE_BUTTON)
            {
                memory.c_factor = tempC_Factor; //revert to old c factor
                signal.error();
                curScreen = HOME;
            }
            else
            {
                int FOUND_IN_MAP = 0;
                for (int i = 0; i < CHARMAP_SIZE; i++)
                {
                    if (c == charMap.key[i])
                    {
                        memory.c_factor += charMap.val[i];
                        FOUND_IN_MAP = 1;
                        break;
                    }
                }
                if (!FOUND_IN_MAP)
                {
                    signal.error(); //pressed invalid key for calibration
                }
            }
        }

        if (curScreen != CALIBRATE)
        {
            return;
        }

        updateCalibrateScreen();
    }
}