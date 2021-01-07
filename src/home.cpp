#include "e3_core.h"
#include "lcd.h"
#include "digital.h"
#include "scale.h"
#include "buttons.h"

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
    String(weight, 1).toCharArray(buf, 8);
    snprintf(line, 17, "WEIGHT:%8sg", buf);
    lcd.home();
    lcd.print(line);

    //second line
    lcd.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        lcd.write(LOCKED);
    }
    else
    {
        lcd.write(UNLOCKED);
    }
    snprintf(line, 17, "SetVal:%-7sg", setValStr);
    lcd.print(line);
}

void home()
{
    relaysOff(); //ensure that all relays are off on home screen

    keypad.setDebounceTime(50);

    for (;;)
    {
        getWeight();

        char c = keypad.getKey();
        setValStr[0] = c;

        // getKeyPressed(); //gets key pressed and writes to global var c

        // handleDigital(); //overrides key pressed if foot switch is pressed

        if (c != '\0') //check if input exists
        {
            if (c == TARE) //tare only works from home screen
            {
                tareScreen();
                tareScale();
                updateHomeScreen();
            }
            else
            {
                // handleKeypad(true);
            }
            break;
            c = '\0'; //consume character
        }

        if (curScreen != HOME)
        {
            return;
        }

        // lcd.home();
        // homeScreen();
        updateHomeScreen();
    }
}