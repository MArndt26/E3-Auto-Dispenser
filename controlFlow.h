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
    switch (curState)
    {
    case HOME_STATE:
        if (c == ENTER) //check if the enter key was pressed
        {
            if (curString == "") //check if user has input data to save
            {
                save();
            }
            else //if no data to save, treat enter as start operation
            {
                curState = RUN_STATE;
            }
        }
        else if (cur_FN_Button != '\0') //check if cur_FN_Button has been previously set
        {
            curState = PRESET_STATE;
        }
        else
        {
            userError("Tried to Change state with curr FN = null");
        }
        break;
    case PRESET_STATE:
        if (cur_FN_Button != c) //check if user has pressed the same fn button twice
        {
            String msg = "Non Consistant State Change Request: " + cur_FN_Button + " -> " + c;
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
            cur_FN_Button = '\0'; //reset cur_FN_Button
            curState = HOME_STATE;
        }
        break;
    case RUN_STATE:
        cur_FN_Button = '\0'; //reset cur_FN_Button
        curState = HOME_STATE;
        break;
    }
    updateScreen();
}

// relaysOff();

// if (c >= '0' && c <= '9') //check if key pressed is in the range [0, 9]
// {
//     if (curString.length() < DISP_SET_STR_MAX_LEN) //check if you are trying to type off the screen
//     {
//         appendChar();
//     }
//     else
//     {
//         userError("in c=[0, 9]");
//     }
// }
// else if (c == '.')
// {
//     if (curString == "")
//     {
//         userError("Cannot Start with dp");
//     }
//     else if (curString[curString.length() - 1] == '.')
//     {
//         userError("Cannot have back-to-back dps");
//     }
//     else if (curString.length() == DISP_SET_STR_MAX_LEN)
//     {
//         userError("Cannot add a dp at end of string");
//     }
//     else if (curString.indexOf(".") != -1)
//     {
//         userError("Cannot have two dps");
//     }
//     else
//     {
//         appendChar();
//     }
// }
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