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

    int val;

    if (curFNButton == FN1_Button)
    {
        val = memory.getFN1();
    }
    else if (curFNButton == FN2_Button)
    {
        val = memory.getFN2();
    }
    else //c == FN3_Button
    {
        val = memory.getFN3();
    }

    //second line
    screen.setCursor(0, 1);
    if (setValStr[0] == '\0')
    {
        snprintf(line, 17, "Cur Val:%7dg", val);
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
    setValStr[0] = '\0'; //clear setValSt

    prevFNButton = curFNButton;
    curFNButton = c;

    if (curFNButton == prevFNButton)
    {
        curScreen = HOME;
    }
}

void handleEnter_program(char c)
{
    if (setValStr[0] != '\0')
    {
        //user is currently setting the value
        int val = atoi(setValStr);
        e3_scale.setSetVal(val);

        if (curFNButton == FN1_Button)
        {
            memory.writeFN1(val);
        }
        else if (curFNButton == FN2_Button)
        {
            memory.writeFN2(val);
        }
        else //curFNButton == FN3_Button
        {
            memory.writeFN3(val);
        }
        setValStr[0] = '\0';
    }
}

void program()
{
    digital.relaysOff(); //ensure that all relays are off on program screen

    screen.clear();

    for (;;)
    {
        char c = keypad.getKey();

#ifdef VIRTUAL_DIGITAL
        if (c == 'f')
#else
        else if (digital.checkFS())
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