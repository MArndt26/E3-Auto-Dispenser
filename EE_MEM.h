/*-------------EEPROM VARS------------*/
//https://www.arduino.cc/en/Reference/EEPROMGet

int eeAddress = 0;

void save()
{
    if (cur_FN_Button == FN1_Button)
    {
        fn1String = curString;
    }
    else if (cur_FN_Button == FN2_Button)
    {
        fn2String = curString;
    }
    else if (cur_FN_Button == FN3_Button)
    {
        fn3String = curString;
    }
    //else not trying to save fn button
    setString = curString;
    curString = "";
}

/* Function reads in the following variables from eeprom memory:
 *      -setStr
 */
void EEPROM_ReadAll()
{
    for (int i = eeAddress; i < eeAddress + DISP_SET_STR_MAX_LEN; i++)
    {
        char c = EEPROM.read(i);

        if (c > '9' || c < '0' || c != '.') //only read in digits and dp as valid input
        {
            setString += ' ';
        }
        else
        {
            setString += c;
        }
    }
}