#include "program.h"
#include "e3_core.h"

// same as above without clearing screen
void updateProgramScreen()
{
    //first line
    char line[17];

    snprintf(line, 17, "PROGR:%c %7sg", curFNButton, setValStr);
    screen.home();
    screen.print(line);

    //second line
    screen.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        snprintf(line, 17, "Cur Val:%7dg", memory.getFN(curFNButton - FN1_Button + 1));
    }
    else
    {
        snprintf(line, 17, "PRESS # to PROGR");
    }
    screen.setCursor(0, 1);
    screen.print(line);
}

void handleNumeric_program(char c)
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

void handleFN_program(char c)
{
    if (setValStr[0] == '\0')
    {
        prevFNButton = curFNButton;
        curFNButton = c;

        if (curFNButton == prevFNButton)
        {
            curScreen = HOME;
        }
    }
    else
    {
        setValStr[0] = '\0'; //clear setValSt
        signal.error();
    }
}

void handleEnter_program(char c)
{
    if (setValStr[0] != '\0')
    {
        //user is currently setting the value
        int val = atoi(setValStr);
        e3_scale.setVal = val;

        memory.writeFN(curFNButton - FN1_Button + 1, val);
        setValStr[0] = '\0';
        signal.success();
        curScreen = HOME;
    }
    else
    {
        signal.error();
    }
}

void program()
{
    digital.relaysOff(); //ensure that all relays are off on program screen
    screen.clear();
    updateProgramScreen();

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
        else if (c != '\0') //check if input exists
        {
            if (c >= '0' && c <= '9')
            {
                handleNumeric_program(c);
            }
            else if (c >= FN1_Button && c <= FN3_Button)
            {
                handleFN_program(c);
            }
            else if (c == ENTER)
            {
                handleEnter_program(c);
            }
            else
            {
                signal.error();
            }
        }

        if (curScreen != PROGRAM)
        {
            return;
        }

        updateProgramScreen();
    }
}