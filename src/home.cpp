#include "home.h"
#include "e3_core.h"

void tareScreen()
{
    screen.clear();
    //first line
    screen.home();
    screen.print("------TARE------");
}

// same as above without clearing screen
void updateHomeScreen()
{
    //first line
    char line[17];

    int whole;
    unsigned int frac;

    floatToString(e3_scale.getWeight(), &whole, &frac);
    snprintf(line, 17, "WEIGHT:%6d.%1ug", whole, frac);
    screen.home();
    screen.print(line);

    //second line
    screen.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        screen.write(screen.LOCKED);
        snprintf(line, 17, "SetVal:%7dg", e3_scale.getSetVal());
    }
    else
    {
        screen.write(screen.UNLOCKED);
        snprintf(line, 17, "SetVal:%7sg", setValStr);
    }
    screen.setCursor(1, 1);
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
    setValStr[0] = '\0'; //clear setValSt
    curFNButton = c;

    curScreen = PRESET;
}

void handleEnter_home(char c)
{
    if (setValStr[0] != '\0')
    {
        //user is currently setting the value
        e3_scale.setSetVal(atoi(setValStr));
        setValStr[0] = '\0';
    }
    else if (HOME_KEYPAD_ENTER)
    {
        curScreen = RUN;
        //go to run state
    }
}

void home()
{
    digital.relaysOff(); //ensure that all relays are off on home screen
    screen.clear();

    for (;;)
    {
        e3_scale.updateWeight();

        char c = keypad.getKey();

#ifdef VIRTUAL_DIGITAL
        if (c == 'f')
#else
        else if (digital.checkFS())
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
                tareScreen();
                e3_scale.tare();
                delay(200);
                updateHomeScreen();
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