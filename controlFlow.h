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
    debugInit();

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
                save();
            }
            else if (setString == "")
            {
                userError("Cannot Run Without Set Val");
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
            userError("Tried to Change state with curr FN = null");
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
                userError("Cannot run null function");
            }
        }
        else if (cur_FN_Button != prev_FN_Button) //check if user has pressed the same fn button twice
        {
            String msg = "Non Consistant State Change Request: ";
            msg += prev_FN_Button;
            msg += " -> ";
            msg += cur_FN_Button;
            userError(msg);
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
                save();
                curState = HOME_STATE;
            }
            else
            {
                userError("User Tried to Save a Null Value");
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
            userError("Cannot Start with dp");
        }
        else if (curString[curString.length() - 1] == '.')
        {
            userError("Cannot have back-to-back dps");
        }
        else if (curString.length() == DISP_SET_STR_MAX_LEN)
        {
            userError("Cannot add a dp at end of string");
        }
        else if (curString.indexOf(".") != -1)
        {
            userError("Cannot have two dps");
        }
        else
        {
            return true;
        }
    }
    else
    {
        String msg = "Unexpected Input Recieved: ";
        msg += c;
        userError(msg);
    }
    return false;
}

void handleInput()
{
    getKeyPressed(); //gets current key char and writes to global c

    if (c != '\0') //check if input exists
    {
        if (curState == RUN_STATE)
        {
            doStateChange(); //break from run state if any key is pressd
        }
        if (c >= FN1_Button && c <= FN3_Button) //function button pressed
        {
            cur_FN_Button = c;
            doStateChange();
        }
        else if (c == '#') //enter button pressed
        {
            doStateChange();
        }
        else if (c >= '0' && c <= '9')
        {
            appendChar();
        }
        else if (c == '.')
        {
            if (curString == "")
            {
                userError("Cannot Start with dp");
            }
            else if (curString[curString.length() - 1] == '.')
            {
                userError("Cannot have back-to-back dps");
            }
            else if (curString.length() == DISP_SET_STR_MAX_LEN)
            {
                userError("Cannot add a dp at end of string");
            }
            else if (curString.indexOf(".") != -1)
            {
                userError("Cannot have two dps");
            }
            else //valid dp was entered
            {
                appendChar();
            }
        }
        else
        {
            String msg = "Unexpected Input Recieved: ";
            msg += c;
            userError(msg);
        }
        debugVars();
        updateScreen();
    }
}