/*-------------EEPROM VALS------------*/
//https://www.arduino.cc/en/Reference/EEPROMGet

int eeAddress = 0;

String setString = "";              //set value saved to eeprom
String fnStrings[3] = {"", "", ""}; //function strings corresponding to fn1, fn2, fn3

void save()
{
    fnStrings[cur_FN_Button - FN1] = curString;
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