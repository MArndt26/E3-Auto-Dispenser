#include "home.h"
#include "e3_core.h"

void tareScreen()
{
    screen.lcd.clear();
    //first line
    screen.lcd.home();
    screen.lcd.print("------TARE------");
}

// same as above without clearing screen
void updateHomeScreen()
{
    //first line
    char line[17];
    char buf[8];
    dtostrf(e3_scale.weight, 8, 1, buf);
    snprintf(line, 17, "WEIGHT:%8sg", buf);
    screen.lcd.home();
    screen.lcd.print(line);

    //second line
    screen.lcd.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        screen.lcd.write(screen.LOCKED);
        snprintf(line, 17, "SetVal:%7dg", e3_scale.setVal);
    }
    else
    {
        screen.lcd.write(screen.UNLOCKED);
        snprintf(line, 17, "SetVal:%7sg", setValStr);
    }
    screen.lcd.setCursor(1, 1);
    screen.lcd.print(line);
}

inline void handleNumeric(char c)
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

inline void handleFN(char c)
{
    //TODO: implement this
    return;
}

inline void handleEnter(char c)
{
    if (setValStr[0] != '\0')
    {
        //user is currently setting the value
        e3_scale.setVal = atoi(setValStr);
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

    e3_scale.setVal = memory.fn1;

    keypad.setDebounceTime(50);

    for (;;)
    {
        e3_scale.getWeight();

        char c = keypad.getKey();

        // handleDigital(); //overrides key pressed if foot switch is pressed

        if (c != '\0') //check if input exists
        {
            if (c >= '0' && c <= '9')
            {
                handleNumeric(c);
            }
            else if (c >= FN1_Button && c <= FN3_Button)
            {
                handleFN(c);
            }
            else if (c == ENTER)
            {
                handleEnter(c);
            }
            else if (c == TARE) //tare only works from home screen
            {
                tareScreen();
                e3_scale.tare();
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