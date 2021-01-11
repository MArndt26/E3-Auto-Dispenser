#include "preset.h"
#include "e3_core.h"

void updatePresetScreen()
{
    char line[17];

    int val = memory.getFN1();

    if (curFNButton == FN2_Button)
    {
        val = memory.getFN2();
    }
    else if (curFNButton == FN3_Button)
    {
        val = memory.getFN3();
    }

    sprintf(line, "PREST:%c %7dg", curFNButton, val);

    screen.home();
    screen.print(line);

    screen.setCursor(0, 1);
    screen.print(" Press # to SET");
}

void handleFN_preset(char c)
{
    prevFNButton = curFNButton;
    curFNButton = c;

    if (curFNButton == prevFNButton)
    {
        curScreen = PROGRAM;
    }
}

void handleEnter_preset(char c)
{
    int val = 0;
    if (c == FN1_Button)
    {
        val = memory.getFN1();
    }
    else if (c == FN2_Button)
    {
        val = memory.getFN2();
    }
    else //c == FN3_Button
    {
        val = memory.getFN3();
    }

    e3_scale.setSetVal(val);

    curScreen = HOME;
}

void preset()
{
    screen.clear();
    digital.relaysOff(); //redundant

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
            if (c >= FN1_Button && c <= FN3_Button)
            {
                handleFN_preset(c);
            }
            else if (c == ENTER)
            {
                handleEnter_preset(c);
            }
            else
            {
                signal.error();
            }
        }

        if (curScreen != PRESET)
        {
            return;
        }
        updatePresetScreen();
    }
}