#include "home.h"
#include "e3_core.h"
#include "common.h"

// same as above without clearing screen
void updateHomeScreen()
{
    //first line
    char line[17];

    int whole;
    unsigned int frac;

    floatToString(e3_scale.weight, &whole, &frac);
#ifdef DEVELOPMENT_MODE
    snprintf(line, 17, "DEVMODE%6d.%1ug", whole, frac);

#else
    snprintf(line, 17, "WEIGHT:%6d.%1ug", whole, frac);
#endif
    screen.home();
    screen.print(line);

    //second line
    screen.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        snprintf(line, 16, "SetVal:%7dg", e3_scale.setVal);
        screen.write(screen.LOCKED);
    }
    else
    {
        snprintf(line, 16, "Setting:%6sg", setValStr);
        screen.write(screen.UNLOCKED);
    }
    // screen.setCursor(0, 1);
    screen.print(line);
}

void handleNumeric_home(char c)
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

void handleFN_home(char c)
{
    if (setValStr[0] == '\0')
    {
        curFNButton = c;
        curScreen = PRESET;
    }
    else
    {
        setValStr[0] = '\0'; //clear setValSt
        signal.error();
    }
}

void handleEnter_home(char c)
{
    if (setValStr[0] != '\0')
    {
        //user is currently setting the value
        e3_scale.setVal = atoi(setValStr);
        setValStr[0] = '\0';
        signal.success();
    }
    else
    {
#ifdef HOME_KEYPAD_ENTER
        curScreen = RUN;
#else
        signal.error();
#endif
    }
}

void home()
{
    digital.relaysOff(); //ensure that all relays are off on home screen
    screen.clear();
    updateHomeScreen();

    for (;;)
    {
        if (!e3_scale.updateWeight(memory.c_factor))
        {
            scaleDisconnectedScreen();
            e3_scale.reconnect();
        }

        char c = keypad.getKey();

#ifdef VIRTUAL_DIGITAL
        if (c == 'f')
#else
        if (digital.checkFS())
#endif
        {
            if (setValStr[0] != '\0')
            {
                signal.error();
            }
            else
            {
                curScreen = RUN;
            }
        }
        else if (c != '\0') //check if input exists
        {
            if (c >= '0' && c <= '9')
            {
                handleNumeric_home(c);
            }
            else if (c >= FN1_Button && c <= FN3_Button)
            {
                handleFN_home(c);
            }
            else if (c == ENTER)
            {
                handleEnter_home(c);
            }
            else if (c == TARE) //tare only works from home screen
            {
                setValStr[0] = '\0';
                tareScreen();
                e3_scale.tare();
                delay(200);
                updateHomeScreen();
            }
            else if (c == CALIBRATE_BUTTON)
            {
                if (setValStr[0] == '\0')
                {
                    curScreen = CALIBRATE;
                }
                else
                {
                    setValStr[0] = '\0';
                    signal.error();
                }
            }
            else
            {
                signal.error();
            }
        }

        if (curScreen != HOME)
        {
            return;
        }

        updateHomeScreen();
    }
}