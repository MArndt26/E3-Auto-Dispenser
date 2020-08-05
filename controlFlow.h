/*----------------CONTROL FLOW VARS---------------*/
const byte NO_INPUT = 0;
const byte INPUT_IS_FN = 1;
const byte INPUT_IS_DIGIT = 2;
const byte INPUT_IS_ENTER = 3;

//TIME VARS
int period = 500;
int frontDelay = 2000;
unsigned long time_now = 0;
byte first = true;

void masterInit()
{
    relayInit();

    debugInit();

    memoryInit();

    scaleInit();

    keypadInit();

    lcdInit();

#if HUSH
    Serial.println("All Modules Initialized");
#endif
}

/*
 * Function doStateChange()
 *  Assumptions: c in range (FN1->FN2) or c = ENTER
 *  
 */
void doStateChange()
{
    switch (curState)
    {
    case HOME_STATE:
        if (c == ENTER) //check if the enter key was pressed
        {
            if (curString != "") //check if user has input data to save
            {
                if (save())
                {
                    userSuccess();
                }
                else
                {
                    userError();
                }
#if HUSH_SUCCESS
                Serial.println("Success: Saved Vars to Memory");
#endif
            }
            else if (setString == "")
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot Run Without Set Val");
#endif
            }
            else //if no data to save, treat enter as start operation
            {
                curState = RUN_STATE;
            }
        }
        else if (cur_FN_Button != '\0') //check if cur_FN_Button has been previously set
        {
            prev_FN_Button = cur_FN_Button; //assign current value to previous
            curState = PRESET_STATE;
        }
        else
        {
            userError();
#if HUSH_ERRORS
            Serial.println("Error: Tried to Change state with curr FN = null");
#endif
        }
        break;
    case PRESET_STATE:
        if (c == ENTER)
        {
            if (c == FN1_Button && fn1String != "")
            {
                curState = RUN_STATE;
            }
            else if (c == FN2_Button && fn2String != "") //Valid (saved) function to run
            {
                curState = RUN_STATE;
            }
            else if (c == FN3_Button && fn3String != "") //Valid (saved) function to run
            {
                curState = RUN_STATE;
            }
            else
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot run null function");
#endif
            }
        }
        else if (cur_FN_Button != prev_FN_Button) //check if user has pressed the same fn button twice
        {
            userError();
#if HUSH_ERRORS
            String msg = "Non Consistant State Change Request: ";
            msg += prev_FN_Button;
            msg += " -> ";
            msg += cur_FN_Button;
            Serial.println(msg);
#endif
        }
        else //user has pressed a function button twice to request program state for that var
        {
            curState = PROGRAM_STATE;
        }
        break;
    case PROGRAM_STATE:
        if (c == ENTER) //user requests to save
        {
            if (curString != "") //Check if there is a valid value to save
            {
                if (save())
                {
                    userSuccess();
                }
                else
                {
                    userError();
                }
#if HUSH_SUCCESS
                Serial.println("Success: Saved Vars to Memory");
#endif
                curState = HOME_STATE;
            }
            else
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: User Tried to Save a Null Value");
#endif
            }
        }
        else //user has pressed a FN button again to escape the programming window
        {
            clearFN_Buttons();
            curState = HOME_STATE;
        }
        break;
    case RUN_STATE:
        clearFN_Buttons();
        curState = HOME_STATE;
        break;
    }
    time_now = millis(); //reset time
    c = '\0';            //consume character used for state change
    curString = "";
}

boolean checkValidInput()
{
    if (c == '.')
    {
        if (curString == "")
        {
            userError();
#if HUSH_ERRORS
            Serial.println("Error: Cannot Start with dp");
#endif
        }
        else if (curString[curString.length() - 1] == '.')
        {
            userError();
#if HUSH_ERRORS
            Serial.println("Error: Cannot have back-to-back dps");
#endif
        }
        else if (curString.length() == DISP_SET_STR_MAX_LEN)
        {
            userError();
#if HUSH_ERRORS
            Serial.println("Error: Cannot add a dp at end of string");
#endif
        }
        else if (curString.indexOf(".") != -1)
        {
            userError();
#if HUSH_ERRORS
            Serial.println("Error: Cannot have two dps");
#endif
        }
        else
        {
            return true;
        }
    }
    else
    {
        userError();
#if HUSH_ERRORS
        String msg = "Unexpected Input Recieved: ";
        msg += c;
        Serial.println(msg);
#endif
    }
    return false;
}

boolean handleFN()
{
    if (c >= FN1_Button && c <= FN3_Button) //function button pressed
    {
        cur_FN_Button = c;
        doStateChange();
        return true;
    }
    return false;
}

void handleKeypad(boolean keypadAllowed)
{
    if (c >= FN1_Button && c <= FN3_Button) //function button pressed
    {
        cur_FN_Button = c;
        doStateChange();
    }
    else if (c == ENTER) //enter button pressed
    {
        doStateChange();
    }
    else if (keypadAllowed)
    {
        if (c >= '0' && c <= '9')
        {
            appendChar();
        }
        else if (c == '.')
        {
            if (curString == "")
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot Start with dp");
#endif
            }
            else if (curString[curString.length() - 1] == '.')
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot have back-to-back dps");
#endif
            }
            else if (curString.length() == DISP_SET_STR_MAX_LEN)
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot add a dp at end of string");
#endif
            }
            else if (curString.indexOf(".") != -1)
            {
                userError();
#if HUSH_ERRORS
                Serial.println("Error: Cannot have two dps");
#endif
            }
            else //valid dp was entered
            {
                appendChar();
            }
        }
        else
        {
            userError();
#if HUSH_ERRORS
            String msg = "Unexpected Input Recieved w/ keypad: ";
            msg += c;
            Serial.println(msg);
#endif
        }
    }
    else
    {
        userError();
#if HUSH_ERRORS
        String msg = "Unexpected Input Recieved w/out keypad: ";
        msg += c;
        Serial.println(msg);
#endif
    }
}

void handleInput()
{
    getWeight(); //gets smoothed weight and assigns to weight string

    getKeyPressed(); //gets current key char and writes to global c

    if (c != '\0') //check if input exists
    {
        switch (curState)
        {
        case HOME_STATE:
            if (c == TARE) //tare only works from home screen
            {
                tareScreen();
                tareScale();
            }
            else
            {
                handleKeypad(true);
            }
            break;
        case PRESET_STATE:
            handleKeypad(false);
            break;
        case PROGRAM_STATE:
            handleKeypad(true);
            break;
        case RUN_STATE:
            doStateChange(); //break from run state if any key is pressd
            break;
        }
        c = '\0'; //consume character
        updateScreenImmediate();
    }
}

void updateScreen()
{
    if (millis() - time_now > period)
    {
        time_now = millis();
        updateScreenImmediate();
    }
}