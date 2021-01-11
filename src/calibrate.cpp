#include "calibrate.h"
#include "e3_core.h"

const char PASSWORD[5] = "1234";
int LOCKED = 1;

#define CHARMAP_SIZE 8
const struct
{
    char key[CHARMAP_SIZE];
    float val[CHARMAP_SIZE];
} charMap = {
    .key = {'1', '2', '3', 'A', '4', '5', '6', 'B'},
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

void tareScreen_calibrate()
{
    screen.clear();
    //first line
    screen.home();
    screen.print("------TARE------");
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
    screen.setCursor(3, 0);
    screen.print("-Incorrect");

    screen.setCursor(4, 1);
    screen.print("Password");
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

        if (c != '\0')
        {
            if (c >= '0' && c <= '9')
            {
                handleNumeric_lock(c);
            }
            else if (c == ENTER)
            {
                handleEnter_lock();
                return;
            }
            else if (c == CALIBRATE_BUTTON)
            {
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

    if (LOCKED)
    {
        incorrectPasswordScreen();
        delay(1000);
        curScreen = HOME;
        return;
    }

    screen.clear();

    for (;;)
    {
        e3_scale.updateWeight(memory.c_factor);

        // using keypad to update factor
        char c = keypad.getKey();

        if (c == TARE)
        {
            tareScreen_calibrate();
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
            signal.error();
            curScreen = HOME;
        }
        else
        {
            for (int i = 0; i < CHARMAP_SIZE; i++)
            {
                if (c == charMap.key[i])
                {
                    memory.c_factor += charMap.val[i];
                    break;
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