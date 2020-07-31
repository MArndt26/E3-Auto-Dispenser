void printLCD();

void userFunctionsInit()
{
    Serial.begin(9600); //for debuggin purposes
    pinMode(errorPin, OUTPUT);
    pinMode(successPin, OUTPUT);

    Serial.println("User Functions Initialized");
}

void userError()
{
    Serial.println("Error");
    digitalWrite(errorPin, HIGH);
    delay(100);
    digitalWrite(errorPin, LOW);
}

void userSuccess()
{
    Serial.println("Success");
    digitalWrite(successPin, HIGH);
    delay(100);
    digitalWrite(successPin, LOW);
}

/*-----------LCD HELPERS---------------*/
void clearDisplay()
{
    curString = "";

    lcd.setCursor(SET_CURSOR_START, SET_LINE_NUMBER);
    lcd.print(setString);

    lcd.setCursor(MASS_CURSOR_START, WEIGHT_LINE_NUMBER);
    lcd.print(curString);
}

void saveScreen()
{
    setString = curString;

    clearDisplay();
}

void appendChar()
{
    lcd.setCursor(SET_MSG.length() + curString.length(), SET_LINE_NUMBER);
    curString += c;
    lcd.print(c);
    printLCD();
}

void printHomePage()
{
    lcd.setCursor(0, WEIGHT_LINE_NUMBER);
    lcd.print(WEIGHT_MSG);
    lcd.print(curString);
    lcd.setCursor(DISP_WEIGHT_STR_MAX_LEN, WEIGHT_LINE_NUMBER);
    lcd.print('g');

    lcd.setCursor(0, SET_LINE_NUMBER);
    lcd.print(SET_MSG);
    lcd.print(setString);
    lcd.setCursor(DISP_SET_STR_MAX_LEN, SET_LINE_NUMBER);
    lcd.print('g');
}

void lcdInit()
{
    lcd.init();
    lcd.backlight();

    printHomePage();
}

/*------------------EERPOM HELPERS--------------------*/

/**Function reads in the following variables from eeprom memory:
 *      -setStr
 **/
void EEPROM_ReadAll()
{
    for (int i = eeAddress; i < eeAddress + DISP_SET_STR_MAX_LEN - SET_MSG.length(); i++)
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
    // setString += '\0';
}

/*-----------------------SCALE HELPERS-----------------------*/
void scaleInit()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    Serial.println("Scale Initialized");
}

/*--------------------RELAY HELPERS------------------------*/
void relaysOn()
{
    digitalWrite(PUMP_CTRL_PIN, HIGH);
    digitalWrite(IO_1_PIN, HIGH);
}

void relaysOff()
{
    digitalWrite(PUMP_CTRL_PIN, LOW);
    digitalWrite(IO_1_PIN, LOW);
}

void relayInit()
{
    pinMode(PUMP_CTRL_PIN, OUTPUT);
    pinMode(IO_1_PIN, OUTPUT);
    relaysOff();
}

/*-----debugging functions-----------*/

void userError(String msg)
{
    Serial.println(msg);
    userError();
}

void userSuccess(String msg)
{
    Serial.println(msg);
    userSuccess();
}

void printLCD()
{
    Serial.println("------------------");
    //first line
    Serial.print("|");
    Serial.print(WEIGHT_MSG);
    Serial.print(curString);
    for (int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - curString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g|");

    //second line
    Serial.print("|");
    Serial.print(SET_MSG);
    Serial.print(curString);
    for (int i = 0; i < DISP_SET_STR_MAX_LEN - setString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g|");

    Serial.println("------------------");
}

void debugVars()
{
    Serial.print("curStr: ");
    Serial.print(curString);
    Serial.print(", setStr: ");
    Serial.print(setString);
    Serial.print(", c: ");
    Serial.print(c);
    Serial.println();
}