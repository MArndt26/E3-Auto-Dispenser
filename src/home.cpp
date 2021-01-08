#include "e3_core.h"
#include "lcd.h"
#include "digital.h"

void tareScreen()
{
    lcd.clear();
    //first line
    lcd.home();
    lcd.print("------TARE------");
}

// same as above without clearing screen
void updateHomeScreen()
{
    //first line
    char line[17];
    char buf[8];
    String(scale.weight, 1).toCharArray(buf, 8);
    snprintf(line, 17, "WEIGHT:%8sg", buf);
    lcd.home();
    lcd.print(line);

    //second line
    lcd.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        lcd.write(LOCKED);
        snprintf(line, 17, "SetVal:%7dg", scale.setVal);
    }
    else
    {
        lcd.write(UNLOCKED);
        snprintf(line, 17, "SetVal:%7sg", setValStr);
    }
    lcd.setCursor(1, 1);
    lcd.print(line);
}

inline void handleNumeric(char c)
{
    bool appended = append(setValStr, SET_VAL_SIZE, c);

    if (!appended)
    {
        // handle overflow
        setValStr[0] = '\0'; //clear string
        userError();
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
        scale.setVal = atoi(setValStr);
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
    relaysOff(); //ensure that all relays are off on home screen

    scale.setVal = memory.fn1;

    keypad.setDebounceTime(50);

    for (;;)
    {
        scale.getWeight();

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
                scale.tare();
                updateHomeScreen();
            }
            else
            {
                userError();
            }
        }

        if (curScreen != HOME)
        {
            return;
        }

        updateHomeScreen();
    }
}