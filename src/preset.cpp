#include "preset.h"
#include "e3_core.h"

void updatePresetScreen()
{
    char line[17];

    sprintf(line, "PREST:%c %7dg", curFNButton, memory.getFN(curFNButton - FN1_Button + 1));

    screen.home();
    screen.print(line);

    screen.setCursor(0, 1);
    screen.print(" Press # to SET");
}

void handleFN_preset(char c)
{
    if (setValStr[0] == '\0')
    {
        prevFNButton = curFNButton;
        curFNButton = c;

        if (curFNButton == prevFNButton)
        {
            curScreen = PROGRAM;
        }
    }
    else
    {
        setValStr[0] = '\0'; //clear setValSt
        signal.error();
    }
}

void handleEnter_preset(char c)
{
    e3_scale.setVal = memory.getFN(curFNButton - FN1_Button + 1);

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