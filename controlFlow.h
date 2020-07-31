void masterInit()
{
    debugInit();

    scaleInit();

    keypadInit();

    lcdInit();

    Serial.println("All Modules Initialized");
}

void getInputs()
{
    getKeyPressed();
    if (c != '\0')
    {
        Serial.print("keyPressed: ");
        Serial.println(c);
    }

    int temp = 0;
    while (Serial.available() > 0)
    {
        c = Serial.read();
        if (temp == 0)
        {
            Serial.print("char: ");
            Serial.println(c);
        }
        else if (c == '$')
        {
            weightString = "";
        }
        else
        {
            weightString += c;
        }
        temp++;
    }
    if (weightString != "")
    {
        Serial.print("Weight: ");
        Serial.println(weightString);
    }
}

/*
 * Function doStateChange()
 *  Assumptions: c in range (FN1->FN2) or c = ENTER
 *  
 */
void doStateChange()
{
    debugVars();
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
            if (fnStrings[c - FN1] != "") //Valid (saved) function to run
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
    c = '\0'; //consume character used for state change
    curString = "";
    updateScreen();
}

boolean checkValidInput()
{
    if (c >= '0' && c <= '9') //check if key pressed is in the range [0, 9]
    {
        if (curString.length() < DISP_SET_STR_MAX_LEN) //check if you are trying to type off the screen
        {
            return true;
        }
        else
        {
            userError("in c=[0, 9]");
        }
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

// relaysOff();

//
// else if (c == '#') //enter key has been pressed
// {
//     if (curString == "") //no user input
//     {
//         userError("Tried to Save Empty String");
//     }
//     else
//     {
//         saveScreen();

//         printLCD();

//         userSuccess();
//     }
// }
// else if (c == CLEAR)
// {
//     clearDisplay();
//     printLCD();
// }
// else if (c == START_STOP)
// {
//     curState = RUN_STATE;
// }
// else if (c >= 'A' && c <= 'D')
// {
//     debugVars();
//     //work with function buttons
// }
// break;

//  relaysOn();
//         if (c == START_STOP)
//         {
//             curState = PROGRAM_STATE;
//             userSuccess("Halted Run State");
//             break;
//         }
//         // if (scale.get_units() >= setString.toFloat())
//         if (c == '$') //for debugging
//         {
//             curState = PROGRAM_STATE;
//             break;
//         }
//         break;